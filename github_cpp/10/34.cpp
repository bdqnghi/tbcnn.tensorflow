#include <iostream>
#include <string>

int main()
{
   std::string string1 = "";
   std::string string2 = "";
   std::cout<<"Enter string01: ";
   std::cin>>string1;
   std::cout<<"Enter string02: ";
   std::cin>>string2;
   int i = 0;
   int j = 0;
   int startPosition1 = -1;
   int startPosition2 = -1;
   int endPosition1 = -1;
   int endPosition2 = -1;
   bool bFoundStartPosition = false;

   while ((i < string1.length()) || (j < string2.length()))
   {
      std::cout<<"i = "<<i<<"j = "<<j<<std::endl;
      std::cout<<"string1 = "<<string1.length()<<"string2 = "<<string2.length()<<std::endl;

      if ((!bFoundStartPosition) && (string1[i] == string2[j]))
      {
         std::cout<<"Found match at i = "<<i<<"j = "<<j<<std::endl;
         startPosition1 = i;
         startPosition2 = j;
         bFoundStartPosition = true;
      }

      else if ((bFoundStartPosition) && (string1[i] == string2[j]))
      {
         std::cout<<"Found match at i = "<<i<<"j = "<<j<<std::endl;

         endPosition1 = i;
         endPosition2 = j;
      }
      else
         ++i;
         ++j;
   }

   std::cout<<"Start Position1 = "<<startPosition1<<std::endl;
   std::cout<<"Start Position2 = "<<startPosition2<<std::endl;
   std::cout<<"End Position1 = "<<endPosition1<<std::endl;
   std::cout<<"End Position2 = "<<endPosition2<<std::endl;

   return 1;
}
