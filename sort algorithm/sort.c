#include <bits/stdc++.h>
using namespace std;

/*插入排序:
	遍历数组，遍历到i时，a0,a1...ai-1是已经排好序的，
	取出ai，从ai-1开始向前和每个比较大小，如果小于，
	则将此位置元素向后移动，继续先前比较，如果不小于，
	则放到正在比较的元素之后.
*/
void insertion_sort(int value[])
{
	int n=10,tmp,j;
	for (int i = 1; i < n; ++i)
	{
		tmp=value[i];
		for (j = i-1;tmp<value[j]&&j>=0;j--)
		{
			value[j+1]=value[j];
		}
		value[j+1]=tmp;
	}

}

/*选择排序:
	原理很简单,从前到后,遍历到第i项,a0,a1...ai-1是已经排好序的，
	然后从i到n选择出最小的，记录下位置，如果不是第i个，则和第i个元素交换。
*/

void selection_sort(int value[]){
	int n=10,tmp,pos,j;
	for(int i=0;i<n-1;i++){
		for(j=i+1,pos=i;j<n;j++){
			if(value[j]<value[pos])
				pos=j;
		}
		if(i!=pos){
			tmp=value[i];
			value[i]=value[pos];
			value[pos]=tmp;
		}
	}
}
/*
冒泡排序:

    比较相邻的元素。如果第一个比第二个大，就交换他们两个。
    对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。
    这步做完后，最后的元素会是最大的数。针对所有的元素重复以上的步骤，
    除了最后一个。持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
优化:
	某一轮结束位置为j，但是这一轮的最后一次交换发生在lastSwap的位置，则lastSwap到j之间是排好序的，
	下一轮的结束点就不必是j--了，而直接到lastSwap即可

*/
void bubble_sort(int value[]){
	int n=10,tmp,pos,lastswap=0;
	for(int i=n-1;i>0;i--){
		lastswap=0;
		for(int j=0;j<i;j++){
			if(value[j+1]<value[j]){
				tmp=value[j+1];
				value[j+1]=value[j];
				value[j]=tmp;
				//最后一次交换位置的坐标
				lastswap=j;
			}
		}
		i=lastswap+1;
	}
}



/*
快速排序:

	快速排序首先找到一个基准，下面程序以第一个元素作为基准（pivot），
	然后先从右向左搜索，如果发现比pivot小，则和pivot交换，然后从左向右搜索，
	如果发现比pivot大，则和pivot交换，一直到左边大于右边，此时pivot左边的都比它小，
	而右边的都比它大，此时pivot的位置就是排好序后应该在的位置，此时pivot将数组划分为左右两部分，
	可以递归采用该方法进行。快排的交换使排序成为不稳定的。
*/

int partition(int value[],int l,int r){
	int base=value[l];
	while(l<r){
		while(l<r&&base<value[r]){
			r--;
		}
		if(l<r){
			value[l]=value[r];
			l++;
		}
		while(l<r&&value[l]<base){
			l++;
		}
		if(l<r){
			value[r]=value[l];
			r--;
		}
	}
	value[l]=base;
	return l;
	

}

void quick_sort(int value[],int l,int r){
	//分而治之
	int q=partition(value, l,r);
	if(l<r){
		//递归调用
		quick_sort(value,l,q-1);
		quick_sort(value,q+1,r);
	}
}

/*
堆排序：
	首先堆是一种特殊的数据结构，它是一个完全二叉树，每个节点的值都大于或等于其左右孩子节点的值，称为大顶堆．
	反之称为小顶堆，堆排序就是利用这种特殊的数据结构，进行排序，一般情况下升序使用大顶堆，降序使用小顶堆．
步骤：
	a.将无需序列构建成一个堆，根据升序降序需求选择大顶堆或小顶堆;

　　　　b.将堆顶元素与末尾元素交换，将最大元素"沉"到数组末端;

　　　　c.重新调整结构，使其满足堆定义，然后继续交换堆顶元素与当前末尾元素，反复执行调整+交换步骤，直到整个序列有序。

	步骤ａ在构建堆的过程是个自低向下的过程，首先从最后一个父节点开始构建：length/2-1,步骤ｃ调整堆的过程，
	是个自顶向下的过程，因为此时子树已经是满足堆的性质了．
*/

void heap_update(int value[],int i,int length){ //i指父节点，length表示子树的长度
	int nchild,tmp;
	//先找到值最大的左右子节点
	for(tmp=value[i];i*2+1<length;i=nchild){
		nchild=2*i+1;
		if(nchild<length-1&&value[nchild+1]>value[nchild])
			nchild++;
		//如果子节点的值大于父节点，交换
		if(value[nchild]>tmp){
			value[i]=value[nchild];
			value[nchild]=tmp;
		}
		//如果父节点的值最大，则退出
		else
			break;
	}

}

void heap_sort(int value[]){
	int length=10,tmp;
	//首先初始化一个大顶堆
	for (int i = length/2-1; i>=0; --i)
	{
		heap_update(value,i,length);
	}
	//将根节点与最后一个节点　值进行交换,且调整子树
	for (int i=length-1; i>0; --i)
	{
      // 把第一个元素和当前的最后一个元素交换，
      // 保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
      //  Swap(&a[0], &a[i]);
		tmp=value[i];
		value[i]=value[0];
		value[0]=tmp;
		// 不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
		heap_update(value, 0, i);	
	}
}

/*
归并排序：
	归并排序是采用分治法（Divide and Conquer）的一个非常典型的应用，将数组二分为最小序列，
	(first+last)/2,再将其合并，首先考虑下如何将将二个有序数列合并。
	这个非常简单，只要从比较二个数列的第一个数，谁小就先取谁，取了后就在对应数列中删除这个数。
	然后再进行比较，如果有数列为空，那直接将另一个数列的数据依次取出即可。
*/



void merge_array(int value[],int first,int mid,int last,int tmp[]){

	int i=first,j=mid,m=mid+1,n=last,k=0;
	while(i<=j&&m<=n){
		if(value[i]>value[m]){
			tmp[k++]=value[m];
			m++;
		}else{
			tmp[k++]=value[i];
			i++;
		}
	}
	while(i<=j){
		tmp[k++]=value[i];
		i++;
	}
	while(m<=n){
		tmp[k++]=value[m];
		m++;
	}
	for (i = 0; i < k; i++)
	        value[first + i] = tmp[i];

}


void merge_sort(int value[],int first,int last,int tmp[]){
	if(first<last){
		int mid=(first+last)/2;
		merge_sort(value,first,mid,tmp);//先将二分之后的左边排好序
		merge_sort(value,mid+1,last,tmp);  //再将二分之后的右边排好序
		merge_array(value,first,mid,last,tmp);  //合并两边的数组
	}
}


/*
希尔排序：
	希尔排序是对插入排序的优化，基于以下两个认识：
	1. 数据量较小时插入排序速度较快，因为n和n2差距很小；
	2. 数据基本有序时插入排序效率很高，因为比较和移动的数据量少。

	 希尔排序的划分子序列不是像归并排序那种的二分，而是采用的叫做增量的技术，
	 例如有十个元素的数组进行希尔排序，首先选择增量为10/2=5，
	 此时第1个元素和第（1+5）个元素配对成子序列使用插入排序进行排序，
	 第2和（2+5）个元素组成子序列，完成后增量继续减半为2，
	 此时第1个元素、第（1+2）、第（1+4）、第（1+6）、第（1+8）个元素组成子序列进行插入排序。
	 这种增量选择方法的好处是可以使数组整体均匀有序，尽可能的减少比较和移动的次数，
	 二分法中即使前一半数据有序，后一半中如果有比较小的数据，还是会造成大量的比较和移动，
	 因此这种增量的方法和插入排序的配合更佳。
*/

void shell_sort(int value[]){
	int length=10,d=length/2,tmp,i,j;
	for(d;d>=1;d=d/2){
		for(i=d;i<length;i++){
			tmp=value[i];
			for(j=i-d;j>=0&&tmp<value[j];j=j-d){
				value[j+d]=value[j];
			}
			value[j+d]=tmp;
		}
	}
}

int main(int argc, char const *argv[])
{
	int tmp[10];
	int value[10]={5,8,1,7,6,2,4,3,0,9};
	shell_sort(value);
	// quick_sort(value, 0, 9);
	merge_sort(value, 0, 9, tmp);
	for (int i = 0; i < 10; ++i)
		{
			printf("%d\t",value[i]);
		}	
	return 0;
}



