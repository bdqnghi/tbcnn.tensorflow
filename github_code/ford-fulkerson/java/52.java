import java.io.*;
import java.util.*;
import java.util.zip.*;
import org.apache.hadoop.io.*;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.conf.*;
import org.apache.hadoop.util.*;

public class main {
	public static void main(String[] oargs) throws Exception {
		Configuration conf = new Configuration();
		String[] args = new GenericOptionsParser(conf, oargs).getRemainingArgs();

		String prog = null;
		List<String> list = new ArrayList<String>();
		for (int i=0; i < args.length; ++i) {
			if ("-D".equals(args[i])){
				String[] ab = args[++i].split("=");
				try { conf.setStrings(ab[0], ab[1]); }
				catch (Exception ex){ System.out.printf("Missing : "+ab[0]); }
			} else if (prog==null){
				prog = args[i];
			} else {
				list.add(args[i]);
			}
		}
		String[] nargs = list.toArray(new String[list.size()]);

		if (prog.equals("ff0")) // the naive Ford Fulkerson
			System.exit(ToolRunner.run(conf, new ff0.FordFulkerson(), nargs));
		else if (prog.equals("ff1"))
			System.exit(ToolRunner.run(conf, new ff1.FordFulkerson(), nargs));
		else if (prog.equals("ff1.input.dimacs"))
			System.exit(ToolRunner.run(conf, new ff1.InputDimacs(), nargs));
		else if (prog.equals("ff1.input.facebook"))
			System.exit(ToolRunner.run(conf, new ff1.InputFacebook(), nargs));
		else if (prog.equals("ff2"))
			System.exit(ToolRunner.run(conf, new ff2.FordFulkerson(), nargs));
		else if (prog.equals("ff3")) // new API, schimmy 
			System.exit(ToolRunner.run(conf, new ff3.FordFulkerson(), nargs));
		else if (prog.equals("ff4")) // no new keyword
			System.exit(ToolRunner.run(conf, new ff4.FordFulkerson(), nargs));
		else if (prog.equals("ff5")) // unlimited K
			System.exit(ToolRunner.run(conf, new ff5.FordFulkerson(), nargs));
		else if (prog.equals("ff6")) // new hadoop
			System.exit(ToolRunner.run(conf, new ff6.FordFulkerson(), nargs));
//		else if (prog.equals("ff7")) // approximation maxflow
//			System.exit(ToolRunner.run(conf, new ff7.FordFulkerson(), nargs));
		else if (prog.equals("ff8")) // ff6 with correct pruning
			System.exit(ToolRunner.run(conf, new ff8.FordFulkerson(), nargs));
		else if (prog.equals("bfs"))
			System.exit(ToolRunner.run(conf, new bfs.bfs(), nargs));
		else 
			System.out.println("No command : " + prog);
	}
}
