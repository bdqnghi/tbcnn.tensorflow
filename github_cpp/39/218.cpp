vector<P> convex(vector<P>p){
	sort(p.begin(),p.end());
	vector<P>ans,S;
    for(int i=0;i<p.size();i++){
    	while(S.size()>=2
    			&& sgn(det(S[S.size()-2],S.back(),p[i]))<=0)
    				S.pop_back();
    	S.push_back(p[i]);
    }//dw
    ans=S;
    S.clear();
	for(int i=(int)p.size()-1;i>=0;i--){
    	while(S.size()>=2
    			&& sgn(det(S[S.size()-2],S.back(),p[i]))<=0)
    				S.pop_back();
    	S.push_back(p[i]);		
	}//up	
	for(int i=1;i+1<S.size();i++)
		ans.push_back(S[i]);
	return ans;
}
