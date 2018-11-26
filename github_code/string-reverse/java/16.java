class stringreverse
    {
        public static void main(String s)
            {
                s=s.trim()+" ";
                int w=0;
                for(int i=0;i<s.length();i++)
                    {
                        if(s.charAt(i)==' ')
                            {
                                for(int x=i-1;x>=w;x--)
                                    {
                                        System.out.print(s.charAt(x));
                                    }
                                System.out.print(" ");
                                w=i;
                            }
                        }
                    }
                }
                 