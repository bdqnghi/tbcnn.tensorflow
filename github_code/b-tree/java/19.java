package canon;

import util.List;

class MoveCall extends tree.Stm
{
    tree.TEMP dst;
    tree.CALL src;
    MoveCall(tree.TEMP d, tree.CALL s)
    {
        dst=d; 
        src=s;
    }
    
    public List<tree.Exp> kids()
    {
        return src.kids();
    }
  
    public tree.Stm build(List<tree.Exp> kids)
    {
        return new tree.MOVE(dst, src.build(kids));
    }
}   
  
class ExpCall extends tree.Stm
{
    tree.CALL call;
    
    ExpCall(tree.CALL c)
    {
        call=c;
    }
    
    public List<tree.Exp> kids()
    {
        return call.kids();
    }
    
    public tree.Stm build(List<tree.Exp> kids)
    {
        return new tree.EXPSTM(call.build(kids));
    }
}   
  
class StmExpList 
{
    tree.Stm stm;
    List<tree.Exp> exps;
    StmExpList(tree.Stm s, List<tree.Exp> e)
    {
        stm=s;
        exps=e;
    }
}

public class Canon
{  
    static boolean isNop(tree.Stm a)
    {
        return a instanceof tree.EXPSTM 
                && ((tree.EXPSTM)a).exp instanceof tree.CONST;
    }

    static tree.Stm seq(tree.Stm a, tree.Stm b)
    {
        if (isNop(a))
            return b;
        else if (isNop(b))
            return a;
        else 
            return new tree.SEQ(a,b);
    }

    static boolean commute(tree.Stm a, tree.Exp b)
    {
        return isNop(a)
                || b instanceof tree.NAME
                || b instanceof tree.CONST;
    }

    static tree.Stm do_stm(tree.SEQ s)
    { 
        return seq(do_stm(s.left), do_stm(s.right));
    }

    static tree.Stm do_stm(tree.MOVE s)
    { 
        if (s.dst instanceof tree.TEMP 
                && s.src instanceof tree.CALL) 
            return reorder_stm(new MoveCall((tree.TEMP)s.dst, (tree.CALL)s.src));
        else if (s.dst instanceof tree.ESEQ)
            return do_stm(new tree.SEQ(((tree.ESEQ)s.dst).stm,
                    new tree.MOVE(((tree.ESEQ)s.dst).exp,
                            s.src)));
        else
            return reorder_stm(s);
 }

    static tree.Stm do_stm(tree.EXPSTM s)
    { 
        if (s.exp instanceof tree.CALL)
            return reorder_stm(new ExpCall((tree.CALL)s.exp));
        else
            return reorder_stm(s);
    }

    static tree.Stm do_stm(tree.Stm s)
    {
        if (s instanceof tree.SEQ)
            return do_stm((tree.SEQ)s);
        else if (s instanceof tree.MOVE)
            return do_stm((tree.MOVE)s);
        else if (s instanceof tree.EXPSTM)
            return do_stm((tree.EXPSTM)s);
        else
            return reorder_stm(s);
    }

    static tree.Stm reorder_stm(tree.Stm s)
    {
        StmExpList x = reorder(s.kids());
        return seq(x.stm, s.build(x.exps));
    }

    static tree.ESEQ do_exp(tree.ESEQ e)
    {
        tree.Stm stms = do_stm(e.stm);
        tree.ESEQ b = do_exp(e.exp);
        
        return new tree.ESEQ(seq(stms,b.stm), b.exp);
    }

    static tree.ESEQ do_exp (tree.Exp e)
    {
        if (e instanceof tree.ESEQ)
            return do_exp((tree.ESEQ)e);
       else
           return reorder_exp(e);
    }
         
    static tree.ESEQ reorder_exp (tree.Exp e)
    {
        StmExpList x = reorder(e.kids());
        return new tree.ESEQ(x.stm, e.build(x.exps));
    }

    static StmExpList nopNull = new StmExpList(new tree.EXPSTM(new tree.CONST(0)),null);

    static StmExpList reorder(List<tree.Exp> exps)
    {
        if (exps==null)
            return nopNull;
        else
        {
            tree.Exp a = exps.head;
            if (a instanceof tree.CALL)
            {
                temp.Temp t = new temp.Temp();
                tree.Exp e = new tree.ESEQ(new tree.MOVE(new tree.TEMP(t), a),
                        new tree.TEMP(t));
                return reorder(new List<tree.Exp>(e, exps.tail));
            } 
            else
            {
                tree.ESEQ aa = do_exp(a);
                StmExpList bb = reorder(exps.tail);
                if (commute(bb.stm, aa.exp))
                    return new StmExpList(seq(aa.stm,bb.stm), 
                            new List<tree.Exp>(aa.exp,bb.exps));
                else
                {
                    temp.Temp t = new temp.Temp();
                        return new StmExpList(
                                seq(aa.stm, 
                                        seq(new tree.MOVE(new tree.TEMP(t),aa.exp),
                                                bb.stm)),
                                new List<tree.Exp>(new tree.TEMP(t), bb.exps));
                }
            }
        }
 }
        
    static List<tree.Stm> linear(tree.SEQ s, List<tree.Stm> l)
    {
        return linear(s.left,linear(s.right,l));
    }
    
    static List<tree.Stm> linear(tree.Stm s, List<tree.Stm> l)
    {
        if (s instanceof tree.SEQ)
            return linear((tree.SEQ)s, l);
        else 
            return new List<tree.Stm>(s,l);
    }

    static public List<tree.Stm> linearize(tree.Stm s)
    {
        return linear(do_stm(s), null);
    }
}
