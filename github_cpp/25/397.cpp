class Solution {
    public:

        vector<vector<int> > permute(vector<int> &num) {
            // Start typing your C/C++ solution below
            // DO NOT write int main() function
            vector<vector<int> > result;
            int n = num.size();

            if (n==1)
            {
                vector<int > one;
                one.push_back(num[0]);
                result.push_back(one);
                return result;
            }

            for (int i=0; i<n; i++)
            {
                int one = num[i];

                vector<int> tmp_num ;
                for (int j=0; j<n; j++)
                {
                    if (j != i)
                        tmp_num.push_back(num[j]);
                }

                vector<vector<int> > tmp_result = permute(tmp_num);

                for (int j=0; j<tmp_result.size(); j++)
                {
                    tmp_result[j].insert(tmp_result[j].begin(), one);
                    result.push_back(tmp_result[j]);
                }
            }


            return result;
        }
};
