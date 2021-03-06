#ifndef MYFUNCTION2_H
#define MYFUNCTION2_H

template<class T1, class T2, class T3>
void myfun2(T1 & map, int *N,int m,int n,Kokkos::View<double **,Kokkos::LayoutRight> & arr2D, T2 & NumNz, T3 & myGlobalElements)
{
  typedef Tpetra::Vector<>::scalar_type scalar_type;
  typedef Tpetra::Map<>::local_ordinal_type local_ordinal_type;
  typedef Tpetra::Map<>::global_ordinal_type global_ordinal_type;
  typedef Tpetra::CrsMatrix<> matrix_type;
  typedef Tpetra::Operator<scalar_type, local_ordinal_type, global_ordinal_type> op_type;
  typedef Tpetra::MultiVector<scalar_type, local_ordinal_type, global_ordinal_type> vec_type;
  typedef Tpetra::Map<local_ordinal_type, global_ordinal_type> map_type;
  typedef typename Kokkos::Details::ArithTraits<scalar_type>::val_type impl_scalar_type;
  typedef  Tpetra::CrsMatrix<>::node_type Node;
  typedef Tpetra::CrsMatrix<>::device_type device_type;
  typedef Tpetra::CrsMatrix<>:: execution_space execution_space;
  typedef Kokkos::CrsMatrix<impl_scalar_type, local_ordinal_type, execution_space> local_matrix_type;
  typedef local_matrix_type::values_type k_values;

//  std::cout<<map->getNodeNumElements();

for(size_t i=0;i<map->getNodeNumElements();i++)
{
  
//   std::cout<<myglobalelements[i]<<std::endl;
 N[0]=-1;
 N[1]=-1;
 N[2]=-1;
 N[3]=-1;

int q=myGlobalElements[i]/m;
int rem =myGlobalElements[i]%m;
  if(q>0)
 {
  N[0]=arr2D(q-1,rem);
 }
if(rem>0)
{
 N[1]=arr2D(q,rem-1);
}

if(q<m-1)
  {
   N[2]=arr2D(q+1,rem);
 }

if(rem<m-1)
  {
   N[3]=arr2D(q,rem+1);

 }

size_t count=0;
  for(int j=0;j<4;j++)
      {
        if(N[j]>=0)
       {
        count=count+1;

       }
      }
  NumNz[i]=count;

for(size_t k=m*n-m;k<m*n;k++)
    {
      if(myGlobalElements[i]==k)
 {
          NumNz[i]=count+1;
        }
     }

for(size_t k=m*n;k<m*n+2*m;k++)
  {

   if (myGlobalElements[i]==k)
   {
     NumNz[i]=1;
    }
  }


}//ends here
}

#endif
