#include "sorting.h"
#include "includes/asp_sorting/misc_sort.h"

#include <algorithm>

namespace sorting
{
    struct populated_inorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = allvals_inorder();
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, allvals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_inorder_test_heapsort_state_sorted);

    struct populated_revorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = allvals_inorder();
		std::reverse( data.begin(), data.end() );
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, allvals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_revorder_test_heapsort_state_sorted);

    struct populated_noorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = allvals_inorder();
		std::random_shuffle( data.begin(), data.end() );
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, allvals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_noorder_test_heapsort_state_sorted);

    struct populated_double_inorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = doublevals_inorder();
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, doublevals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_inorder_test_heapsort_state_sorted);

    struct populated_double_revorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = doublevals_inorder();
		std::reverse( data.begin(), data.end() );
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, doublevals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_revorder_test_heapsort_state_sorted);

    struct populated_double_noorder_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = doublevals_inorder();
		std::random_shuffle( data.begin(), data.end() );
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, doublevals_inorder());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_double_noorder_test_heapsort_state_sorted);

    struct populated_multiple_same_elem_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = multiple_same_val();
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, multiple_same_val());
	    }
    };
    ENABLE_TEST(access_test_set(),populated_multiple_same_elem_test_heapsort_state_sorted);

    struct populated_two_inorder_elem_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {9,10};
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, {9,10});
	    }
    };
    ENABLE_TEST(access_test_set(),populated_two_inorder_elem_test_heapsort_state_sorted);

    struct populated_two_revorder_elem_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {10,9};
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, {9,10});
	    }
    };
    ENABLE_TEST(access_test_set(),populated_two_revorder_elem_test_heapsort_state_sorted);

    struct populated_single_elem_test_heapsort_state_sorted
	: public sorting_test_case
    {
	TEST_INSERTER;
    	void configure()
	    {
		data = {10};
	    }
	test_result run()
	    {
		heapsort(data);
		return compare_test(data, {10});
	    }
    };
    ENABLE_TEST(access_test_set(),populated_single_elem_test_heapsort_state_sorted);
}
