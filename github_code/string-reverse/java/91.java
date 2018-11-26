package org.biomart.processors.sequence;

import static com.google.common.base.Strings.isNullOrEmpty;
import static java.sql.ResultSet.CONCUR_READ_ONLY;
import static java.sql.ResultSet.TYPE_FORWARD_ONLY;
import static org.biomart.processors.sequence.Sequence.closeSilently;

import java.io.IOException;
import java.io.OutputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.biomart.common.exceptions.BioMartException;
import org.biomart.common.exceptions.TechnicalException;
import org.biomart.common.exceptions.ValidationException;
import org.biomart.common.resources.Log;
import org.biomart.configurator.utils.McUtils;

/**
 *
 * @author jhsu, jguberman
 */
public abstract class SequenceParser implements SequenceConstants {

    protected static boolean isDebug = Boolean.getBoolean("biomart.debug");

    private List<List<String>> headerInfo;
    private PreparedStatement pstmtStart = null;
    private PreparedStatement pstmtMiddle = null;
    private PreparedStatement pstmtEnd = null;

    // Flank info
    protected int downstreamFlank = 0;
    protected int upstreamFlank = 0;

	// Size of each block of sequence in the database, currently {@value}
	protected static final int CHUNK_SIZE = 100000;

    protected int extraAttributes = 0;

    protected final int headerStartCol;

    protected OutputStream out;

    protected SequenceParser(int headerStartCol) {
        this.headerStartCol = headerStartCol;
    }

    public abstract String parseLine(String[] line);
    public abstract String parseLast();

    public abstract SequenceParser validate() throws ValidationException;

    public SequenceParser setOutputStream(OutputStream out) {
        this.out = out;
        return this;
    }

    /** Given a chromosome name, start coordinate, and end coordinate,
	 * returns the corresponding sequence.
	 *
	 * @param seqChrName	Chromosome name.
	 * @param seqStart	Sequence start position. If < 0, is changed to 0.
	 * @param seqEnd	Sequence end position.
	 * @return	Sequence from given region.
	 * @throws TechnicalException
	 */
	public String getSequence(String seqChrName, final int start, final int end) {
        return getSequence(seqChrName, false, start, end);
    }

	public String getSequence(String seqChrName, List<Position> positions) {
        return getSequence(seqChrName, false, positions);
    }

	public String getSequence(String seqChrName, boolean reverseCompliment, final int start, final int end) {
        List<Position> positions = new ArrayList<Position>() {{
            add(new Position(start, end));
        }};
        return getSequence(seqChrName, reverseCompliment, positions);
    }

	public String getSequence(String seqChrName, boolean reverseComplement, List<Position> positions) {
		StringBuilder retrievedSequence = new StringBuilder();
        ResultSet rs = null;

		try {
            // Set chromosome name
            pstmtStart.setString(3, seqChrName);
            pstmtMiddle.setString(1, seqChrName);
            pstmtEnd.setString(3, seqChrName);

            for (Position pos : positions) {
                int start = pos.start;
                int end = pos.end;

                if (start < 1){
                    start = 1;
                    System.err.println("Sequence start cannot be less than 1, changing to 1");
                }

                if (end < 0 || "".equals(seqChrName) || end-start+1 < 1){
                    continue;
                }

                pstmtStart.setInt(1, ((start-1)%CHUNK_SIZE) + 1);
                pstmtStart.setInt(2, Math.min((end-start/CHUNK_SIZE*CHUNK_SIZE)+1, CHUNK_SIZE+1)-start%CHUNK_SIZE);
                pstmtStart.setInt(4, start);
                pstmtStart.setInt(5, CHUNK_SIZE-1);
                pstmtStart.setInt(6, start);

            	if (SequenceMain.TURN_ON_TIMING) McUtils.timing1();	// to isolate exon/cdna/coding bottleneck (see JIRA DCCTEST-1667); TODO remove when fixed
                rs = pstmtStart.executeQuery();
                if (SequenceMain.TURN_ON_TIMING) McUtils.timing2();

                if (rs.next()) {
                    String seq = rs.getString(1);
                    retrievedSequence.append(seq);

					closeSilently(rs);

					// Do chunks and end
					if ((pos.start-1)/CHUNK_SIZE != (pos.end-1)/CHUNK_SIZE){
						pstmtMiddle.setInt(2, end/CHUNK_SIZE*CHUNK_SIZE);
						pstmtMiddle.setInt(3, CHUNK_SIZE-1);
						pstmtMiddle.setInt(4, 1+(1+start/CHUNK_SIZE)*CHUNK_SIZE);

						rs = pstmtMiddle.executeQuery();

						while (rs.next()) {
							seq = rs.getString(1);
							retrievedSequence.append(seq);
						}

						closeSilently(rs);

						pstmtEnd.setInt(1, 1);
						pstmtEnd.setInt(2, end%CHUNK_SIZE);
						pstmtEnd.setInt(4, end);
						pstmtEnd.setInt(5, CHUNK_SIZE-1);
						pstmtEnd.setInt(6, end);

						rs = pstmtEnd.executeQuery();
						

						rs.next();
						retrievedSequence.append(rs.getString(1));

						closeSilently(rs);
					}
				}
            }

		} catch (SQLException e){
            Log.error(e);
            throw new BioMartException("Error retrieving sequence", e);
		} finally {
            closeSilently(rs);
        }

		return retrievedSequence.toString();
	}

	/**
	 * Given a sequence, prints FASTA formatted output
	 *
	 * @param sequence The sequence to be printed.
	 * @param header The header to be printed above the sequence (optional).
	 * @param lineLength The length of each sequence line (optional; default 60).
	 * @param isProtein If true, translate the DNA sequence to protein sequence (optional, default false).
	 */
	protected String getFASTA(String sequence, String header, int lineLength) {
        StringBuilder sb = new StringBuilder();

		if (isNullOrEmpty(sequence) || sequence.equals("null")){
            Log.debug("Sequence was null or empty: " + header);
			sequence = SEQUENCE_UNAVAILABLE;
		}

        sb.append(">").append(header).append("\n");

        int sequenceLength = sequence.length();

        for(int i = 0; i < sequenceLength; i+=lineLength){
            sb.append(sequence.substring(i,Math.min(i+lineLength,sequenceLength))).append("\n");
        }
        return sb.toString();
	}
	protected String getFASTA(String sequence, int lineLength) {
		return getFASTA(sequence, "", lineLength);
	}
	protected String getFASTA(String sequence, String header) {
		return getFASTA(sequence, header, 60);
	}
	protected String getFASTA(String sequence) {
		return getFASTA(sequence, "", 60);
	}

	/**
	 * Returns the reverse complement of a DNA or RNA sequence.
	 * @param sequence The input sequence as a String.
	 * @return	The reverse complement sequence as a String.
	 */
	protected final String getReverseComplement(String sequence){
		// I'm sure there are better and faster ways to do this, but this will work for now
		if(sequence == null){
			return null;
		}
		StringBuilder reversed = new StringBuilder(sequence.length());
		for (int i = sequence.length()-1;i >= 0;--i){
			switch (sequence.charAt(i)) {
			case 'A': reversed.append('T'); break;
			case 'T': reversed.append('A'); break;
			case 'C': reversed.append('G'); break;
			case 'G': reversed.append('C'); break;
			case 'U': reversed.append('A'); break;
			case 'R': reversed.append('Y'); break;
			case 'Y': reversed.append('R'); break;
			case 'K': reversed.append('M'); break;
			case 'M': reversed.append('K'); break;
			case 'S': reversed.append('S'); break;
			case 'W': reversed.append('W'); break;
			case 'B': reversed.append('V'); break;
			case 'V': reversed.append('B'); break;
			case 'D': reversed.append('H'); break;
			case 'H': reversed.append('D'); break;
			/*			case 'N': reversed.append('N'); break;
			case 'X': reversed.append('X'); break;
			case '-': reversed.append('-'); break;*/
			default: reversed.append(sequence.charAt(i)); break;
			}
		}
		return reversed.toString();
	}

	/**
	 * Checks that one and only one entry of flank is greater than zero.
	 * @param flank The array containing the flank parameters
	 */
	protected final void checkFlank() throws ValidationException {
        if (upstreamFlank == 0 && downstreamFlank == 0){
            throw new ValidationException("Validation Error: Requests for flank sequence must be accompanied by an upstream_flank or downstream_flank request");
        } else if (upstreamFlank > 0 && downstreamFlank> 0){
            throw new ValidationException("Validation Error: For this sequence option choose upstream OR downstream flanking sequence, NOT both.");
        } else if (upstreamFlank < 0 || downstreamFlank < 0){
            throw new ValidationException("Validation Error: Flank distance can not be negative.");
        }
	}

    protected final String getHeader() {
        String[] arr = new String[headerInfo.size()];
        int i = 0;
        for (List<String> values : headerInfo) {
            arr[i++] = StringUtils.join(values, HEADER_VALUE_DELIMITER);
        }
        return StringUtils.join(arr, HEADER_COLUMN_DELIMITER);
    }

    protected final void storeHeaderInfo(String[] line) {
        for (int i=0; i<extraAttributes; i++) {
			if (headerStartCol + i >= line.length) {
				break;
			}
            String curr = line[headerStartCol+i];
            List<String> prev = headerInfo.get(i);
            if (!prev.contains(curr)) {
                prev.add(curr);
            }
        }
    }

    protected final void clearHeader() {
        headerInfo = new ArrayList<List<String>>();
        for (int i=0; i<extraAttributes; i++) {
            headerInfo.add(new ArrayList<String>());
        }
    }


	/**
	 * Disconnects from the database at the end of execution.
	 */
	protected boolean done(boolean isDone) {
        try {
            if (!isDone) {
                String lastSequence = parseLast();
                if (!"".equals(lastSequence)) {
                    out.write(lastSequence.getBytes());
                    return true;
                }
            }
        } catch (IOException e) {
            Log.error("Problem writing to OutputStream", e);
        } finally {
            closeSilently(pstmtStart);
            closeSilently(pstmtMiddle);
            closeSilently(pstmtEnd);
        }
        return false;
    }

	protected void startup() {}

    public final SequenceParser prepareStatements(Connection conn, String tableName) {
        try {
            String sqlQueryStart = String.format("SELECT substring(sequence,?,?) FROM %s WHERE chr_name = ? AND chr_start <= ? AND chr_start + ? >= ?;",
                    tableName);
            String sqlQuery = String.format("SELECT sequence FROM %s WHERE chr_name = ? AND chr_start <= ? AND chr_start + ? >= ? ORDER BY chr_start;",
                    tableName);
            String sqlQueryEnd = String.format("SELECT substring(sequence,?,?) FROM %s WHERE chr_name = ? AND chr_start <= ? AND chr_start + ? >= ?;",
                    tableName);

            pstmtStart = conn.prepareStatement(sqlQueryStart, TYPE_FORWARD_ONLY, CONCUR_READ_ONLY);
            pstmtMiddle = conn.prepareStatement(sqlQuery, TYPE_FORWARD_ONLY, CONCUR_READ_ONLY);
            pstmtEnd = conn.prepareStatement(sqlQueryEnd, TYPE_FORWARD_ONLY, CONCUR_READ_ONLY);
            pstmtStart.setFetchSize(Integer.MIN_VALUE);
            pstmtMiddle.setFetchSize(Integer.MIN_VALUE);
            pstmtEnd.setFetchSize(Integer.MIN_VALUE);

        } catch(Exception e) {
            throw new BioMartException(e);
        }
        return this;
    }

    public final SequenceParser setExtraAttributes(int num) {
        extraAttributes = num;
        return this;
    }

    public final SequenceParser setDownstreamFlank(int i) {
        downstreamFlank = i;
        return this;
    }

    public final SequenceParser setUpstreamFlank(int i) {
        upstreamFlank = i;
        return this;
    }
    private static final char[] REVERSE_COMPLEMENTS = new char[255];

    // Initialize Ascii mapping (including extended)
    static {
        REVERSE_COMPLEMENTS[0] = 0; // \u0000
        REVERSE_COMPLEMENTS[1] = 0; // \u0001
        REVERSE_COMPLEMENTS[2] = 0; // \u0002
        REVERSE_COMPLEMENTS[3] = 0; // \u0003
        REVERSE_COMPLEMENTS[4] = 0; // \u0004
        REVERSE_COMPLEMENTS[5] = 0; // \u0005
        REVERSE_COMPLEMENTS[6] = 0; // \u0006
        REVERSE_COMPLEMENTS[7] = 0; // \u0007
        REVERSE_COMPLEMENTS[8] = 0; // \b
        REVERSE_COMPLEMENTS[9] = 0; // \t
        REVERSE_COMPLEMENTS[10] = 0; // \n
        REVERSE_COMPLEMENTS[11] = 0; // \u000B
        REVERSE_COMPLEMENTS[12] = 0; // \f
        REVERSE_COMPLEMENTS[13] = 0; // \r
        REVERSE_COMPLEMENTS[14] = 0; // \u000E
        REVERSE_COMPLEMENTS[15] = 0; // \u000F
        REVERSE_COMPLEMENTS[16] = 0; // \u0010
        REVERSE_COMPLEMENTS[17] = 0; // \u0011
        REVERSE_COMPLEMENTS[18] = 0; // \u0012
        REVERSE_COMPLEMENTS[19] = 0; // \u0013
        REVERSE_COMPLEMENTS[20] = 0; // \u0014
        REVERSE_COMPLEMENTS[21] = 0; // \u0015
        REVERSE_COMPLEMENTS[22] = 0; // \u0016
        REVERSE_COMPLEMENTS[23] = 0; // \u0017
        REVERSE_COMPLEMENTS[24] = 0; // \u0018
        REVERSE_COMPLEMENTS[25] = 0; // \u0019
        REVERSE_COMPLEMENTS[26] = 0; // \u001A
        REVERSE_COMPLEMENTS[27] = 0; // \u001B
        REVERSE_COMPLEMENTS[28] = 0; // \u001C
        REVERSE_COMPLEMENTS[29] = 0; // \u001D
        REVERSE_COMPLEMENTS[30] = 0; // \u001E
        REVERSE_COMPLEMENTS[31] = 0; // \u001F
        REVERSE_COMPLEMENTS[32] = 0; //
        REVERSE_COMPLEMENTS[33] = '!'; // !
        REVERSE_COMPLEMENTS[34] = '"'; // \"
        REVERSE_COMPLEMENTS[35] = '#'; // #
        REVERSE_COMPLEMENTS[36] = '$'; // $
        REVERSE_COMPLEMENTS[37] = '%'; // %
        REVERSE_COMPLEMENTS[38] = '&'; // &
        REVERSE_COMPLEMENTS[39] = '\''; // '
        REVERSE_COMPLEMENTS[40] = '('; // (
        REVERSE_COMPLEMENTS[41] = ')'; // )
        REVERSE_COMPLEMENTS[42] = '*'; // *
        REVERSE_COMPLEMENTS[43] = '+'; // +
        REVERSE_COMPLEMENTS[44] = ','; // ,
        REVERSE_COMPLEMENTS[45] = '-'; // -
        REVERSE_COMPLEMENTS[46] = '.'; // .
        REVERSE_COMPLEMENTS[47] = '/'; // \/
        REVERSE_COMPLEMENTS[48] = '0'; // 0
        REVERSE_COMPLEMENTS[49] = '1'; // 1
        REVERSE_COMPLEMENTS[50] = '2'; // 2
        REVERSE_COMPLEMENTS[51] = '3'; // 3
        REVERSE_COMPLEMENTS[52] = '4'; // 4
        REVERSE_COMPLEMENTS[53] = '5'; // 5
        REVERSE_COMPLEMENTS[54] = '6'; // 6
        REVERSE_COMPLEMENTS[55] = '7'; // 7
        REVERSE_COMPLEMENTS[56] = '8'; // 8
        REVERSE_COMPLEMENTS[57] = '9'; // 9
        REVERSE_COMPLEMENTS[58] = ':'; // :
        REVERSE_COMPLEMENTS[59] = ';'; // ;
        REVERSE_COMPLEMENTS[60] = '<'; // <
        REVERSE_COMPLEMENTS[61] = '='; // =
        REVERSE_COMPLEMENTS[62] = '>'; // >
        REVERSE_COMPLEMENTS[63] = '?'; // ?
        REVERSE_COMPLEMENTS[64] = '@'; // @
        REVERSE_COMPLEMENTS[65] = 'T'; // A
        REVERSE_COMPLEMENTS[66] = 'V'; // B
        REVERSE_COMPLEMENTS[67] = 'G'; // C
        REVERSE_COMPLEMENTS[68] = 'H'; // D
        REVERSE_COMPLEMENTS[69] = 'E'; // E
        REVERSE_COMPLEMENTS[70] = 'F'; // F
        REVERSE_COMPLEMENTS[71] = 'C'; // G
        REVERSE_COMPLEMENTS[72] = 'D'; // H
        REVERSE_COMPLEMENTS[73] = 'I'; // I
        REVERSE_COMPLEMENTS[74] = 'J'; // J
        REVERSE_COMPLEMENTS[75] = 'M'; // K
        REVERSE_COMPLEMENTS[76] = 'L'; // L
        REVERSE_COMPLEMENTS[77] = 'K'; // M
        REVERSE_COMPLEMENTS[78] = 'N'; // N
        REVERSE_COMPLEMENTS[79] = 'O'; // O
        REVERSE_COMPLEMENTS[80] = 'P'; // P
        REVERSE_COMPLEMENTS[81] = 'Q'; // Q
        REVERSE_COMPLEMENTS[82] = 'Y'; // R
        REVERSE_COMPLEMENTS[83] = 'S'; // S
        REVERSE_COMPLEMENTS[84] = 'A'; // T
        REVERSE_COMPLEMENTS[85] = 'U'; // U
        REVERSE_COMPLEMENTS[86] = 'B'; // V
        REVERSE_COMPLEMENTS[87] = 'W'; // W
        REVERSE_COMPLEMENTS[88] = 'X'; // X
        REVERSE_COMPLEMENTS[89] = 'R'; // Y
        REVERSE_COMPLEMENTS[90] = 'z'; // Z
        REVERSE_COMPLEMENTS[91] = '['; // [
        REVERSE_COMPLEMENTS[92] = '\\'; // \\
        REVERSE_COMPLEMENTS[93] = ']'; // ]
        REVERSE_COMPLEMENTS[94] = '^'; // ^
        REVERSE_COMPLEMENTS[95] = '_'; // _
        REVERSE_COMPLEMENTS[96] = '`'; // `
        REVERSE_COMPLEMENTS[97] = 'a'; // a
        REVERSE_COMPLEMENTS[98] = 'b'; // b
        REVERSE_COMPLEMENTS[99] = 'c'; // c
        REVERSE_COMPLEMENTS[100] = 'd'; // d
        REVERSE_COMPLEMENTS[101] = 'e'; // e
        REVERSE_COMPLEMENTS[102] = 'f'; // f
        REVERSE_COMPLEMENTS[103] = 'g'; // g
        REVERSE_COMPLEMENTS[104] = 'h'; // h
        REVERSE_COMPLEMENTS[105] = 'i'; // i
        REVERSE_COMPLEMENTS[106] = 'j'; // j
        REVERSE_COMPLEMENTS[107] = 'k'; // k
        REVERSE_COMPLEMENTS[108] = 'l'; // l
        REVERSE_COMPLEMENTS[109] = 'm'; // m
        REVERSE_COMPLEMENTS[110] = 'n'; // n
        REVERSE_COMPLEMENTS[111] = 'o'; // o
        REVERSE_COMPLEMENTS[112] = 'p'; // p
        REVERSE_COMPLEMENTS[113] = 'q'; // q
        REVERSE_COMPLEMENTS[114] = 'r'; // r
        REVERSE_COMPLEMENTS[115] = 's'; // s
        REVERSE_COMPLEMENTS[116] = 't'; // t
        REVERSE_COMPLEMENTS[117] = 'u'; // u
        REVERSE_COMPLEMENTS[118] = 'v'; // v
        REVERSE_COMPLEMENTS[119] = 'w'; // w
        REVERSE_COMPLEMENTS[120] = 'x'; // x
        REVERSE_COMPLEMENTS[121] = 'y'; // y
        REVERSE_COMPLEMENTS[122] = 'z'; // z
        REVERSE_COMPLEMENTS[123] = '{'; // {
        REVERSE_COMPLEMENTS[124] = '|'; // |
        REVERSE_COMPLEMENTS[125] = '}'; // }
        REVERSE_COMPLEMENTS[126] = '~'; // ~
        REVERSE_COMPLEMENTS[127] = 0; // 
        REVERSE_COMPLEMENTS[128] = 0; // \u0080
        REVERSE_COMPLEMENTS[129] = 0; // \u0081
        REVERSE_COMPLEMENTS[130] = 0; // \u0082
        REVERSE_COMPLEMENTS[131] = 0; // \u0083
        REVERSE_COMPLEMENTS[132] = 0; // \u0084
        REVERSE_COMPLEMENTS[133] = 0; // \u0085
        REVERSE_COMPLEMENTS[134] = 0; // \u0086
        REVERSE_COMPLEMENTS[135] = 0; // \u0087
        REVERSE_COMPLEMENTS[136] = 0; // \u0088
        REVERSE_COMPLEMENTS[137] = 0; // \u0089
        REVERSE_COMPLEMENTS[138] = 0; // \u008A
        REVERSE_COMPLEMENTS[139] = 0; // \u008B
        REVERSE_COMPLEMENTS[140] = 0; // \u008C
        REVERSE_COMPLEMENTS[141] = 0; // \u008D
        REVERSE_COMPLEMENTS[142] = 0; // \u008E
        REVERSE_COMPLEMENTS[143] = 0; // \u008F
        REVERSE_COMPLEMENTS[144] = 0; // \u0090
        REVERSE_COMPLEMENTS[145] = 0; // \u0091
        REVERSE_COMPLEMENTS[146] = 0; // \u0092
        REVERSE_COMPLEMENTS[147] = 0; // \u0093
        REVERSE_COMPLEMENTS[148] = 0; // \u0094
        REVERSE_COMPLEMENTS[149] = 0; // \u0095
        REVERSE_COMPLEMENTS[150] = 0; // \u0096
        REVERSE_COMPLEMENTS[151] = 0; // \u0097
        REVERSE_COMPLEMENTS[152] = 0; // \u0098
        REVERSE_COMPLEMENTS[153] = 0; // \u0099
        REVERSE_COMPLEMENTS[154] = 0; // \u009A
        REVERSE_COMPLEMENTS[155] = 0; // \u009B
        REVERSE_COMPLEMENTS[156] = 0; // \u009C
        REVERSE_COMPLEMENTS[157] = 0; // \u009D
        REVERSE_COMPLEMENTS[158] = 0; // \u009E
        REVERSE_COMPLEMENTS[159] = 0; // \u009F
        REVERSE_COMPLEMENTS[160] = 0; // \u00A0
        REVERSE_COMPLEMENTS[161] = 0; // \u00A1
        REVERSE_COMPLEMENTS[162] = 0; // \u00A2
        REVERSE_COMPLEMENTS[163] = 0; // \u00A3
        REVERSE_COMPLEMENTS[164] = 0; // \u00A4
        REVERSE_COMPLEMENTS[165] = 0; // \u00A5
        REVERSE_COMPLEMENTS[166] = 0; // \u00A6
        REVERSE_COMPLEMENTS[167] = 0; // \u00A7
        REVERSE_COMPLEMENTS[168] = 0; // \u00A8
        REVERSE_COMPLEMENTS[169] = 0; // \u00A9
        REVERSE_COMPLEMENTS[170] = 0; // \u00AA
        REVERSE_COMPLEMENTS[171] = 0; // \u00AB
        REVERSE_COMPLEMENTS[172] = 0; // \u00AC
        REVERSE_COMPLEMENTS[173] = 0; // \u00AD
        REVERSE_COMPLEMENTS[174] = 0; // \u00AE
        REVERSE_COMPLEMENTS[175] = 0; // \u00AF
        REVERSE_COMPLEMENTS[176] = 0; // \u00B0
        REVERSE_COMPLEMENTS[177] = 0; // \u00B1
        REVERSE_COMPLEMENTS[178] = 0; // \u00B2
        REVERSE_COMPLEMENTS[179] = 0; // \u00B3
        REVERSE_COMPLEMENTS[180] = 0; // \u00B4
        REVERSE_COMPLEMENTS[181] = 0; // \u00B5
        REVERSE_COMPLEMENTS[182] = 0; // \u00B6
        REVERSE_COMPLEMENTS[183] = 0; // \u00B7
        REVERSE_COMPLEMENTS[184] = 0; // \u00B8
        REVERSE_COMPLEMENTS[185] = 0; // \u00B9
        REVERSE_COMPLEMENTS[186] = 0; // \u00BA
        REVERSE_COMPLEMENTS[187] = 0; // \u00BB
        REVERSE_COMPLEMENTS[188] = 0; // \u00BC
        REVERSE_COMPLEMENTS[189] = 0; // \u00BD
        REVERSE_COMPLEMENTS[190] = 0; // \u00BE
        REVERSE_COMPLEMENTS[191] = 0; // \u00BF
        REVERSE_COMPLEMENTS[192] = 0; // \u00C0
        REVERSE_COMPLEMENTS[193] = 0; // \u00C1
        REVERSE_COMPLEMENTS[194] = 0; // \u00C2
        REVERSE_COMPLEMENTS[195] = 0; // \u00C3
        REVERSE_COMPLEMENTS[196] = 0; // \u00C4
        REVERSE_COMPLEMENTS[197] = 0; // \u00C5
        REVERSE_COMPLEMENTS[198] = 0; // \u00C6
        REVERSE_COMPLEMENTS[199] = 0; // \u00C7
        REVERSE_COMPLEMENTS[200] = 0; // \u00C8
        REVERSE_COMPLEMENTS[201] = 0; // \u00C9
        REVERSE_COMPLEMENTS[202] = 0; // \u00CA
        REVERSE_COMPLEMENTS[203] = 0; // \u00CB
        REVERSE_COMPLEMENTS[204] = 0; // \u00CC
        REVERSE_COMPLEMENTS[205] = 0; // \u00CD
        REVERSE_COMPLEMENTS[206] = 0; // \u00CE
        REVERSE_COMPLEMENTS[207] = 0; // \u00CF
        REVERSE_COMPLEMENTS[208] = 0; // \u00D0
        REVERSE_COMPLEMENTS[209] = 0; // \u00D1
        REVERSE_COMPLEMENTS[210] = 0; // \u00D2
        REVERSE_COMPLEMENTS[211] = 0; // \u00D3
        REVERSE_COMPLEMENTS[212] = 0; // \u00D4
        REVERSE_COMPLEMENTS[213] = 0; // \u00D5
        REVERSE_COMPLEMENTS[214] = 0; // \u00D6
        REVERSE_COMPLEMENTS[215] = 0; // \u00D7
        REVERSE_COMPLEMENTS[216] = 0; // \u00D8
        REVERSE_COMPLEMENTS[217] = 0; // \u00D9
        REVERSE_COMPLEMENTS[218] = 0; // \u00DA
        REVERSE_COMPLEMENTS[219] = 0; // \u00DB
        REVERSE_COMPLEMENTS[220] = 0; // \u00DC
        REVERSE_COMPLEMENTS[221] = 0; // \u00DD
        REVERSE_COMPLEMENTS[222] = 0; // \u00DE
        REVERSE_COMPLEMENTS[223] = 0; // \u00DF
        REVERSE_COMPLEMENTS[224] = 0; // \u00E0
        REVERSE_COMPLEMENTS[225] = 0; // \u00E1
        REVERSE_COMPLEMENTS[226] = 0; // \u00E2
        REVERSE_COMPLEMENTS[227] = 0; // \u00E3
        REVERSE_COMPLEMENTS[228] = 0; // \u00E4
        REVERSE_COMPLEMENTS[229] = 0; // \u00E5
        REVERSE_COMPLEMENTS[230] = 0; // \u00E6
        REVERSE_COMPLEMENTS[231] = 0; // \u00E7
        REVERSE_COMPLEMENTS[232] = 0; // \u00E8
        REVERSE_COMPLEMENTS[233] = 0; // \u00E9
        REVERSE_COMPLEMENTS[234] = 0; // \u00EA
        REVERSE_COMPLEMENTS[235] = 0; // \u00EB
        REVERSE_COMPLEMENTS[236] = 0; // \u00EC
        REVERSE_COMPLEMENTS[237] = 0; // \u00ED
        REVERSE_COMPLEMENTS[238] = 0; // \u00EE
        REVERSE_COMPLEMENTS[239] = 0; // \u00EF
        REVERSE_COMPLEMENTS[240] = 0; // \u00F0
        REVERSE_COMPLEMENTS[241] = 0; // \u00F1
        REVERSE_COMPLEMENTS[242] = 0; // \u00F2
        REVERSE_COMPLEMENTS[243] = 0; // \u00F3
        REVERSE_COMPLEMENTS[244] = 0; // \u00F4
        REVERSE_COMPLEMENTS[245] = 0; // \u00F5
        REVERSE_COMPLEMENTS[246] = 0; // \u00F6
        REVERSE_COMPLEMENTS[247] = 0; // \u00F7
        REVERSE_COMPLEMENTS[248] = 0; // \u00F8
        REVERSE_COMPLEMENTS[249] = 0; // \u00F9
        REVERSE_COMPLEMENTS[250] = 0; // \u00FA
        REVERSE_COMPLEMENTS[251] = 0; // \u00FB
        REVERSE_COMPLEMENTS[252] = 0; // \u00FC
        REVERSE_COMPLEMENTS[253] = 0; // \u00FD
        REVERSE_COMPLEMENTS[254] = 0; // \u00FE
    }
}
