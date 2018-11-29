package com.enbecko.nbmodmaker.linalg.real;

import javax.annotation.Nullable;
import java.util.Arrays;

/**
 * Created by enbec on 12.07.2017.
 */
public class Real_Matrix_MxN {
    final float[][] content;
    final int size;
    int m, n;
    protected boolean isTransposed = false;
    protected boolean isMuted = false;

    public Real_Matrix_MxN(int m, int n) {
        this.content = new float[m][n];
        this.m = m;
        this.n = n;
        this.size = m * n;
    }

    public Real_Matrix_MxN(int m, int n, float... content) {
        this(m, n);
        this.fillWithContent(content);
    }

    public Real_Matrix_MxN(int m, Real_Vec_n[] columns) {
        this(m, columns.length);
        for (int nC = 0; nC < columns.length; nC++) {
            if (columns[nC].getSize() == this.m) {
                this.setColumn(nC, columns[nC]);
            } else
                throw new RuntimeException("Tried to initialize a matrix with m = " + m + " but this column vec: \n" + columns[nC]);
        }
    }

    public Real_Matrix_MxN(Real_Vec_n[] rows, int n) {
        this(rows.length, n);
        for (int mC = 0; mC < rows.length; mC++) {
            if (rows[mC].getSize() == this.n) {
                this.setRow(mC, rows[mC]);
            } else
                throw new RuntimeException("Tried to initialize a matrix with m = " + m + " but this row vec: \n" + rows[mC]);
        }
    }

    public Real_Matrix_MxN(Real_Matrix_MxN other) {
        this(other.getM(), other.getN());
        this.fillWithContent(other);
    }

    public static void main(String[] args) {
        Real_Matrix_MxN lhs = new Real_Matrix_MxN(4, 4,
                1, 2, 3, 4,
                5, 6, 7, 8,
                9, 10, 11, 12,
                13, 14, 15, 16);
        Vec4 lhs_2 = new Vec4(1, 2, 3, 1);
        Vec4 rhs = new Vec4(5, 6, 7, 0.125F);
        System.out.println(lhs_2.toIdentWithOffset(2));
        long time = System.currentTimeMillis();
    }

    public float[][] getContentAsCopy() {
        return Arrays.copyOf(this.content, this.content.length);
    }

    public boolean isTransposed() {
        return this.isTransposed;
    }

    public boolean isMuted() {
        return this.isMuted;
    }

    public float getAt(int mC, int nC) {
        if (!this.isTransposed) {
            if (mC < this.m && nC < this.n)
                return this.content[mC][nC];
        } else if (nC < this.m && mC < this.n)
            return this.content[nC][mC];
        return Float.NaN;
    }

    public void setAt(int mC, int nC, float content) {
        if (!this.isMuted) {
            if (!this.isTransposed) {
                if (mC < this.m && nC < this.n)
                    this.content[mC][nC] = content;
            } else if (nC < this.m && mC < this.n)
                this.content[nC][mC] = content;
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public void setColumn(int nC, Real_Vec_n column) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            if (column.getSize() == thisM) {
                if (nC < thisN) {
                    for (int mCC = 0; mCC < thisM; mCC++) {
                        this.content[!this.isTransposed ? mCC : nC][!this.isTransposed ? nC : mCC] = column.content[mCC][0];
                    }
                }
            } else
                throw new RuntimeException("can't insert \n" + column + " as column at " + nC + " in \n" + this);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public void setRow(int mC, Real_Vec_n row) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            if (row.getSize() == thisN) {
                if (mC < thisM) {
                    for (int nCC = 0; nCC < thisN; nCC++) {
                        this.content[!this.isTransposed ? mC : nCC][!this.isTransposed ? nCC : mC] = row.content[nCC][0];
                    }
                }
            } else {
                throw new RuntimeException("can't insert \n" + row + " as row at " + mC + " in \n" + this);
            }
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN setMuted(boolean mute) {
        this.isMuted = mute;
        return this;
    }

    public Real_Matrix_MxN setTransposed(boolean transposed) {
        if (!this.isMuted) {
            this.isTransposed = transposed;
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
        return this;
    }

    public int getM() {
        return !this.isTransposed ? this.m : this.n;
    }

    public int getN() {
        return !this.isTransposed ? this.n : this.m;
    }

    public int getSize() {
        return this.size;
    }

    public boolean isSquare() {
        return this.m == this.n;
    }

    public void fillWithContent(float... content) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            fillLoop:
            for (int mC = 0; mC < thisM; mC++) {
                for (int nC = 0; nC < thisN; nC++) {
                    if (mC * thisN + nC < content.length) {
                        this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = content[(!this.isTransposed ? mC : nC) * thisN + (!this.isTransposed ? nC : mC)];
                    } else
                        break fillLoop;
                }
            }
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN fillWithContent(Real_Matrix_MxN other) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            int rhsM = !other.isTransposed ? other.m : other.n;
            int rhsN = !other.isTransposed ? other.n : other.m;
            if (thisM == rhsM && thisN == rhsN) {
                for (int mC = 0; mC < thisM; mC++) {
                    for (int nC = 0; nC < thisN; nC++) {
                        this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = other.content[!other.isTransposed ? mC : nC][!this.isTransposed ? nC : mC];
                    }
                }
            }
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
        return this;
    }

    public Real_Matrix_MxN toIdentWithOffset(int off) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            if (off < thisM) {
                for (int mC = 0; mC < thisM; mC++) {
                    for (int nC = 0; nC < thisN; nC++) {
                        int t;
                        this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = (((t = mC - off) >= 0 ? t : thisM + t) == nC ? 1 : 0);
                    }
                }
            } else
                throw new RuntimeException("Can't make \n" + this + " to ident with offset: " + off);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
        return this;
    }

    public Real_Matrix_MxN swapRows(int m1, int m2) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            if (m1 < thisM && m2 < thisM) {
                for (int nC = 0; nC < thisN; nC++) {
                    float tmp = this.content[!this.isTransposed ? m1 : nC][!this.isTransposed ? nC : m1];
                    this.content[!this.isTransposed ? m1 : nC][!this.isTransposed ? nC : m1] = this.content[!this.isTransposed ? m2 : nC][!this.isTransposed ? nC : m2];
                    this.content[!this.isTransposed ? m2 : nC][!this.isTransposed ? nC : m2] = tmp;
                }
            }
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
        return this;
    }

    public Real_Matrix_MxN swapColumns(int n1, int n2) {
        if (!this.isMuted) {
            int thisM = !this.isTransposed ? this.m : this.n;
            int thisN = !this.isTransposed ? this.n : this.m;
            if (n1 < thisN && n2 < thisN) {
                for (int mC = 0; mC < thisM; mC++) {
                    float tmp = this.content[this.isTransposed ? n1 : mC][this.isTransposed ? mC : n1];
                    this.content[this.isTransposed ? n1 : mC][this.isTransposed ? mC : n1] = this.content[this.isTransposed ? n2 : mC][this.isTransposed ? mC : n2];
                    this.content[this.isTransposed ? n2 : mC][this.isTransposed ? mC : n2] = tmp;
                }
            }
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
        return this;
    }

    public Real_Matrix_MxN mul(Real_Matrix_MxN rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        int rhsM = !rhs.isTransposed ? rhs.m : rhs.n;
        int rhsN = !rhs.isTransposed ? rhs.n : rhs.m;
        if (thisN == rhsM || (rhsN == 1 && rhsM >= thisN)) {
            Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != rhsN) ? new Real_Matrix_MxN(thisM, rhsN) : fill;
            float val;
            for (int mC = 0; mC < thisM; mC++) {
                for (int nC = 0; nC < rhsN; nC++) {
                    val = 0;
                    for (int mnC = 0; mnC < (thisM < rhsM ? thisM : rhsM); mnC++) {
                        val += !this.isTransposed && !rhs.isTransposed ? this.content[mC][mnC] * rhs.content[mnC][nC] :
                                this.isTransposed && !rhs.isTransposed ? this.content[mnC][mC] * rhs.content[mnC][nC] :
                                        !this.isTransposed ? this.content[mC][mnC] * rhs.content[nC][mnC] :
                                                this.content[mnC][mC] * rhs.content[nC][mnC];
                    }
                    out.setAt(mC, nC, val);
                }
            }
            return out;
        } else
            throw new RuntimeException("This matrix-multiplication is not possible: \n" + this + " * \n" + rhs);
    }

    public Real_Matrix_MxN mulToThis(Real_Matrix_MxN rhs) {
        if (!this.isMuted) {
            Real_Matrix_MxN newOne = new Real_Matrix_MxN(this.getM(), this.getN());
            if (this.isSquare() && rhs.isSquare() && this.size == rhs.size) {
                this.fillWithContent(this.mul(rhs, newOne));
                return this;
            } else
                throw new RuntimeException("Can't mul \n" + rhs + " to this \n" + this);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN add(Real_Matrix_MxN rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        int rhsM = !rhs.isTransposed ? rhs.m : rhs.n;
        int rhsN = !rhs.isTransposed ? rhs.n : rhs.m;
        if (thisM == rhsM && thisN == rhsN) {
            Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
            float val;
            for (int mC = 0; mC < thisM; mC++) {
                for (int nC = 0; nC < thisN; nC++) {
                    out.content[!out.isTransposed ? mC : nC][!out.isTransposed ? nC : mC] =
                            this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] +
                                    rhs.content[!rhs.isTransposed ? mC : nC][!rhs.isTransposed ? nC : mC];
                }
            }
            return out;
        } else
            throw new RuntimeException("This matrix-multiplication is not possible: \n" + this + " * \n" + rhs);
    }

    public Real_Matrix_MxN addToThis(Real_Matrix_MxN rhs) {
        if (!this.isMuted) {
            return this.add(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN addToThis(float rhs) {
        if (!this.isMuted) {
            return this.add(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN newAdd(Real_Matrix_MxN rhs) {
        return this.add(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public Real_Matrix_MxN sub(Real_Matrix_MxN rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        int rhsM = !rhs.isTransposed ? rhs.m : rhs.n;
        int rhsN = !rhs.isTransposed ? rhs.n : rhs.m;
        if (thisM == rhsM && thisN == rhsN) {
            Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
            float val;
            for (int mC = 0; mC < thisM; mC++) {
                for (int nC = 0; nC < thisN; nC++) {
                    out.content[!out.isTransposed ? mC : nC][!out.isTransposed ? nC : mC] =
                            this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] -
                                    rhs.content[!rhs.isTransposed ? mC : nC][!rhs.isTransposed ? nC : mC];
                }
            }
            return out;
        } else
            throw new RuntimeException("This matrix-multiplication is not possible: \n" + this + " * \n" + rhs);
    }

    public Real_Matrix_MxN subFromThis(Real_Matrix_MxN rhs) {
        if (!this.isMuted) {
            return this.sub(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN subFromThis(float rhs) {
        if (!this.isMuted) {
            return this.sub(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN newSub(Real_Matrix_MxN rhs) {
        return this.add(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public Real_Matrix_MxN mul(float rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
        for (int mC = 0; mC < thisM; mC++) {
            for (int nC = 0; nC < thisN; nC++) {
                out.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] * rhs;
            }
        }
        return out;
    }

    public Real_Matrix_MxN mulToThis(float rhs) {
        if (!this.isMuted) {
            return this.mul(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN newMul(float rhs) {
        return this.mul(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public Real_Matrix_MxN add(float rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
        for (int mC = 0; mC < thisM; mC++) {
            for (int nC = 0; nC < thisN; nC++) {
                out.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] + rhs;
            }
        }
        return out;
    }

    public Real_Matrix_MxN newAdd(float rhs) {
        return this.add(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public Real_Matrix_MxN sub(float rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
        for (int mC = 0; mC < thisM; mC++) {
            for (int nC = 0; nC < thisN; nC++) {
                out.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] - rhs;
            }
        }
        return out;
    }

    public Real_Matrix_MxN newSub(float rhs) {
        return this.add(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public Real_Matrix_MxN div(float rhs, @Nullable Real_Matrix_MxN fill) {
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        Real_Matrix_MxN out = fill == null || (fill.getM() != thisM && fill.getN() != thisN) ? this : fill;
        for (int mC = 0; mC < thisM; mC++) {
            for (int nC = 0; nC < thisN; nC++) {
                out.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] = this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC] / rhs;
            }
        }
        return out;
    }

    public Real_Matrix_MxN divToThis(float rhs) {
        if (!this.isMuted) {
            return this.div(rhs, null);
        } else
            throw new RuntimeException(this + "\n is muted and you can't change it");
    }

    public Real_Matrix_MxN newDiv(float rhs) {
        return this.add(rhs, new Real_Matrix_MxN(this.getM(), this.getN()));
    }

    public String toString() {
        StringBuilder builder = new StringBuilder();
        int thisM = !this.isTransposed ? this.m : this.n;
        int thisN = !this.isTransposed ? this.n : this.m;
        int[] longest = new int[thisN];
        for (int nC = 0; nC < thisN; nC++) {
            int tmp;
            for (int mC = 0; mC < thisM; mC++)
                if ((tmp = String.valueOf(this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC]).length()) > longest[nC])
                    longest[nC] = tmp;
        }
        for (int mC = 0; mC < thisM; mC++) {
            builder.append("| ");
            for (int nC = 0; nC < thisN; nC++) {
                String tm = String.valueOf(this.content[!this.isTransposed ? mC : nC][!this.isTransposed ? nC : mC]);
                for (int nn = 0; nn < (longest[nC] - tm.length()) / 2; nn++)
                    builder.append(' ');
                builder.append(tm);
                for (int nn = 0; nn < Math.ceil((longest[nC] - tm.length()) / 2f) + 1; nn++)
                    builder.append(' ');
            }
            builder.append("|\n");
        }
        return builder.toString();
    }
}
