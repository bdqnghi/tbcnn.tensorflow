

#include <shogun/lib/config.h>
#include <shogun/lib/SGVector.h>
#include <shogun/lib/SGSparseMatrix.h>
#include <shogun/lib/SGSparseVector.h>
#include <shogun/base/Parameter.h>
#include <shogun/mathematics/linalg/linop/SparseMatrixOperator.h>
#include <shogun/mathematics/eigen3.h>

namespace shogun
{

template<class T>
CSparseMatrixOperator<T>::CSparseMatrixOperator()
	: CMatrixOperator<T>()
	{
		init();
	}

template<class T>
CSparseMatrixOperator<T>::CSparseMatrixOperator(SGSparseMatrix<T> op)
	: CMatrixOperator<T>(op.num_features),
	  m_operator(op)
	{
		init();
	}

template<class T>
CSparseMatrixOperator<T>::CSparseMatrixOperator
	(const CSparseMatrixOperator<T>& orig)
	: CMatrixOperator<T>(orig.get_dimension())
	{
		init();

		typedef SGSparseVector<T> vector;
		typedef SGSparseVectorEntry<T> entry;

		m_operator=SGSparseMatrix<T>(orig.m_operator.num_vectors, orig.m_operator.num_features);

		vector* rows=SG_MALLOC(vector, m_operator.num_features);
		for (index_t i=0; i<m_operator.num_vectors; ++i)
		{
			entry* features=SG_MALLOC(entry, orig.m_operator[i].num_feat_entries);
			for (index_t j=0; j<orig.m_operator[i].num_feat_entries; ++j)
			{
				features[j].feat_index=orig.m_operator[i].features[j].feat_index;
				features[j].entry=orig.m_operator[i].features[j].entry;
			}
			rows[i].features=features;
			rows[i].num_feat_entries=m_operator[i].num_feat_entries;
		}
		m_operator.sparse_matrix=rows;

		SG_SGCDEBUG("%s deep copy created (%p)\n", this->get_name(), this);
	}

template<class T>
void CSparseMatrixOperator<T>::init()
	{
		CSGObject::set_generic<T>();

		this->m_parameters->add_vector(&m_operator.sparse_matrix,
				&m_operator.num_vectors, "sparse_matrix",
				"The sparse matrix of the linear operator.");
		this->m_parameters->add(&m_operator.num_features,
				"m_operator.num_features", "Number of features.");
	}

template<class T>
CSparseMatrixOperator<T>::~CSparseMatrixOperator()
	{
	}

template<class T>
SGSparseMatrix<T> CSparseMatrixOperator<T>::get_matrix_operator() const
	{
		return m_operator;
	}

#ifdef HAVE_EIGEN3
template<class T>
SparsityStructure* CSparseMatrixOperator<T>::get_sparsity_structure(
	int64_t power) const
	{
		REQUIRE(power>0, "matrix-power is non-positive!\n");

		
		CSparseMatrixOperator<bool>* sp_str
			=static_cast<CSparseMatrixOperator<bool>*>(*this);

		
		Eigen::SparseMatrix<bool> current_power
			=EigenSparseUtil<bool>::toEigenSparse(sp_str->get_matrix_operator());

		
		Eigen::SparseMatrix<bool> matrix_power;

		
		
		
		bool lsb=true;
		while (power)
		{
			
			if (1 & power)
			{
				if (lsb)
				{
					
					
					matrix_power=current_power;
					lsb=false;
				}
				else
					matrix_power=matrix_power*current_power;
			}
			power=power>>1;

			
			if (power)
				current_power=current_power*current_power;
		}

		
		int32_t* outerIndexPtr=const_cast<int32_t*>(matrix_power.outerIndexPtr());
		int32_t* innerIndexPtr=const_cast<int32_t*>(matrix_power.innerIndexPtr());

		SG_UNREF(sp_str);

		return new SparsityStructure(outerIndexPtr, innerIndexPtr,
			matrix_power.rows());
	}
#else
template<class T>
SparsityStructure* CSparseMatrixOperator<T>::get_sparsity_structure(
	int64_t power) const
	{
		SG_SWARNING("Eigen3 required\n");
		return new SparsityStructure();
	}
#endif 

template<> \
SparsityStructure* CSparseMatrixOperator<complex128_t>
	::get_sparsity_structure(int64_t power) const
  {
    SG_SERROR("Not supported for complex128_t\n");
    return new SparsityStructure();
  }

template<class T>
SGVector<T> CSparseMatrixOperator<T>::get_diagonal() const
	{
		REQUIRE(m_operator.sparse_matrix, "Operator not initialized!\n");

		const int32_t diag_size=m_operator.num_vectors>m_operator.num_features ?
			m_operator.num_features : m_operator.num_vectors;

		SGVector<T> diag(diag_size);
		diag.set_const(static_cast<T>(0));
		for (index_t i=0; i<diag_size; ++i)
		{
			SGSparseVectorEntry<T>* current_row=m_operator[i].features;
			for (index_t j=0; j<m_operator[i].num_feat_entries; ++j)
			{
				if (i==current_row[j].feat_index)
				{
					diag[i]=current_row[j].entry;
					break;
				}
			}
		}

		return diag;
	}

template<class T>
void CSparseMatrixOperator<T>::set_diagonal(SGVector<T> diag)
	{
		REQUIRE(m_operator.sparse_matrix, "Operator not initialized!\n");
		REQUIRE(diag.vector, "Diagonal not initialized!\n");

		const int32_t diag_size=m_operator.num_vectors>m_operator.num_features ?
			m_operator.num_features : m_operator.num_vectors;

		REQUIRE(diag_size==diag.vlen, "Dimension mismatch!\n");

		bool need_sorting=false;
		for (index_t i=0; i<diag_size; ++i)
		{
			SGSparseVectorEntry<T>* current_row=m_operator[i].features;
			bool inserted=false;
			
			for (index_t j=0; j<m_operator[i].num_feat_entries; ++j)
			{
				if (i==current_row[j].feat_index)
				{
					current_row[j].entry=diag[i];
					inserted=true;
					break;
				}
			}

			
			if (!inserted)
			{
				index_t j=m_operator[i].num_feat_entries;
				m_operator[i].num_feat_entries=j+1;
				m_operator[i].features=SG_REALLOC(SGSparseVectorEntry<T>,
					m_operator[i].features, j, j+1);
				m_operator[i].features[j].feat_index=i;
				m_operator[i].features[j].entry=diag[i];
				need_sorting=true;
			}
		}

		if (need_sorting)
			m_operator.sort_features();
	}

template<class T>
SGVector<T> CSparseMatrixOperator<T>::apply(SGVector<T> b) const
	{
		REQUIRE(m_operator.sparse_matrix, "Operator not initialized!\n");
		REQUIRE(this->get_dimension()==b.vlen,
			"Number of rows of vector must be equal to the "
			"number of cols of the operator!\n");

		SGVector<T> result(m_operator.num_vectors);
		result=m_operator*b;

		return result;
	}

#define UNDEFINED(type) \
template<> \
SGVector<type> CSparseMatrixOperator<type>::apply(SGVector<type> b) const \
	{	\
		SG_SERROR("Not supported for %s\n", #type);\
		return b; \
	}

UNDEFINED(bool)
UNDEFINED(char)
UNDEFINED(int8_t)
UNDEFINED(uint8_t)
UNDEFINED(int16_t)
UNDEFINED(uint16_t)
UNDEFINED(int32_t)
UNDEFINED(uint32_t)
UNDEFINED(int64_t)
UNDEFINED(uint64_t)
UNDEFINED(float32_t)
UNDEFINED(floatmax_t)
#undef UNDEFINED

template class CSparseMatrixOperator<bool>;
template class CSparseMatrixOperator<char>;
template class CSparseMatrixOperator<int8_t>;
template class CSparseMatrixOperator<uint8_t>;
template class CSparseMatrixOperator<int16_t>;
template class CSparseMatrixOperator<uint16_t>;
template class CSparseMatrixOperator<int32_t>;
template class CSparseMatrixOperator<uint32_t>;
template class CSparseMatrixOperator<int64_t>;
template class CSparseMatrixOperator<uint64_t>;
template class CSparseMatrixOperator<float32_t>;
template class CSparseMatrixOperator<float64_t>;
template class CSparseMatrixOperator<floatmax_t>;
template class CSparseMatrixOperator<complex128_t>;
}
