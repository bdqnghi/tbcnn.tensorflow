
/*
   Description: This example demonstrates basic usage of the Bloom filter.
                Initially some values are inserted then they are subsequently
                queried, noting any false positives or errors.
*/


#include <iostream>
#include <string>

#include "bloom_filter.hpp"
using namespace std;

int main()
{

   bloom_parameters parameters;

   // How many elements roughly do we expect to insert?
   parameters.projected_element_count = 1000;

   // Maximum tolerable false positive probability? (0,1)
   parameters.false_positive_probability = 0.0001; // 1 in 10000

   // Simple randomizer (optional)
   parameters.random_seed = 0xA5A5A5A5;

   if (!parameters)
   {
      cout << "Error - Parametros mal inicializados!" << endl;
      return 1;
   }

   parameters.compute_optimal_parameters();

   //Instantiate Bloom Filter
   bloom_filter filter(parameters);

   string str_list[] = { "AbC", "iJk", "XYZ" };

   // Insert into Bloom Filter
   {
      // Insert some strings
      for (size_t i = 0; i < (sizeof(str_list) / sizeof(string)); ++i)
      {
         filter.insert(str_list[i]);
      }

      // Insert some numbers
      for (size_t i = 0; i < 100; ++i)
      {
         filter.insert(i);
      }
   }

   // Query Bloom Filter
   {
      // Query the existence of strings
      for (size_t i = 0; i < (sizeof(str_list) / sizeof(string)); ++i)
      {
         if (filter.contains(str_list[i]))
         {
            cout << "BF contains: " << str_list[i] << endl;
         }
      }

      // Query the existence of numbers
      for (size_t i = 100; i < 200; ++i)
      {
         if (filter.contains(i))
         {
            cout << "BF contains: " << i << endl;
         }
      }

      string invalid_str_list[] = { "AbCX", "iJkX", "XYZX" };

      // Query the existence of invalid strings
      for (size_t i = 0; i < (sizeof(invalid_str_list) / sizeof(string)); ++i)
      {
         if (filter.contains(invalid_str_list[i]))
         {
            cout << "BF falsely contains: " << invalid_str_list[i] << endl;
         }
      }

      // Query the existence of invalid numbers
      for (int i = -1; i > -100; --i)
      {
         if (filter.contains(i))
         {
            cout << "BF falsely contains: " << i << endl;
         }
      }
   }

   return 0;
}
