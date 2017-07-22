#include "SortingAlgorithims.h"


SortAlg::SortAlg()
{
  //constructor
}

SortAlg::~SortAlg()
{
  //destructor
}

SortAlg::SortAlg(SortAlg &copy)
{
  //copy constructor
}

void SortAlg::Set(string inc_val_n_loc){
    string temp_string = inc_val_n_loc;

    int new_start = 0;
    int end_loc = 0;
    int num_of_items = 0;

    for(int j = 0; j < (signed)temp_string.size(); j++) //walk through string to find ; indicating number of items to create
    {
        if (temp_string[j] == ';') {num_of_items++;}
    }
    num_of_items++;//to account for last element not ending with ';'


     vector<Item> working_vector(num_of_items);//vector of size 1, will add dynamically

    for(int i = 0; i < num_of_items;i++)
    {
        end_loc = temp_string.find(";");
        new_start = end_loc;
        new_start++;
        working_vector[i].segment = temp_string.substr(0, end_loc);

        temp_string = temp_string.substr(new_start);// remove segment from temp_string

        working_vector[i].value = stoi(working_vector[i].segment.substr(0,working_vector[i].segment.find(","))); //value from segment to working value
        int index_start = working_vector[i].segment.find(",");
        index_start++;
        working_vector[i].index = stoi(working_vector[i].segment.substr(index_start)); //index from segment to working index
    }

    m_string = working_vector;


}//end set

void SortAlg::insertion(){
    vector<Item> work_vec = this->m_string;//copy m_string to work_vec

    int p = 0;//first iterator for passes
    int j = 0;//second iterator for going back

    ///testing
    cout << "Set is now: " << endl;
           for(int i = 0; (unsigned)i < work_vec.size(); i++)
            cout << work_vec[i].value << "," << work_vec[i].index << endl;
    ///


    int array_size = work_vec.size(); //number of items in work_vec

    ///test
    cout << "array_size" << array_size << endl;
    ///

    for(p = 1; p < array_size; ++p) //pass for number of items
    {
        Item temp = std::move(work_vec[p]); //store value at p to temp

        ///
        //cout << temp.value << "," << temp.index << ";";
        ///

        for(j = p; j > 0 && temp.value < work_vec[j - 1].value; --j) //set j to p ; loop j until it checks all items going back & while current item is less than the prev item
        {
            work_vec[j] = std::move(work_vec[j-1]); //bring prev item forward 1
            ///work_vec[j].index = temp.index;
        }
         ///maybe remove
         ///temp.index = work_vec[j].index;//fix index before swap
         work_vec[j] = std::move(temp); //bring current item back 1
    }

    ///print insertion
    cout << "Set is now: " << endl;
           for(int i = 0; (unsigned)i < work_vec.size(); i++)
            cout << work_vec[i].value << "," << work_vec[i].index << ";" << endl;;
    //
}//end insertion

void SortAlg::shell(int gap1, int gap2, int gap3){
    vector<Item> work_vec = m_string;

    cout << "running shell" << endl;

    //sort by gap
    //use modified insertion sort
    int array_size = work_vec.size();
    int p;
    int j;

   ///testing
    cout << "Set is now: " << endl;
           for(int i = 0; (unsigned)i < work_vec.size(); i++)
            cout << work_vec[i].value << "," << work_vec[i].index << endl;
    ///

    for(int p = gap1; p < array_size; p+=gap1)
    {
        Item temp = std::move(work_vec[p]);

        for(j = p; j > 0 && temp.value < work_vec[j-gap1].value; j-=gap1)
        {
            work_vec[j] = std::move(work_vec[j-gap1]);
        }
            work_vec[j] = std::move(temp);
    }

    ///gap2
    for(int p = gap2; p < array_size; p+=gap2)
    {
        Item temp = std::move(work_vec[p]);

        for(j = p; j > 0 && temp.value < work_vec[j-gap2].value; j-=gap2)
        {
            work_vec[j] = std::move(work_vec[j-gap2]);
        }
            work_vec[j] = std::move(temp);
    }

    ///gap3
    for(int p = gap3; p < array_size; p+=gap3)
    {
        Item temp = std::move(work_vec[p]);

        for(j = p; j > 0 && temp.value < work_vec[j-gap3].value; j-=gap3)
        {
            work_vec[j] = std::move(work_vec[j-gap3]);
        }
            work_vec[j] = std::move(temp);
    }

    ///print shell
    cout << "Set is now: " << endl;
           for(int i = 0; (unsigned)i < work_vec.size(); i++)
            cout << work_vec[i].value << "," << work_vec[i].index << ";" << endl;;
    //

}//end shell

void SortAlg::merge_sort() {

    vector<Item> tempArr1 = this->m_string;
    vector<Item> tempArr2(tempArr1.size());

    merge_sort(tempArr1, tempArr2, 0, tempArr1.size()-1);

    ///print final merge
    cout << "Final Set is now:------------------------------------------------------------------ " << endl;
           for(int i = 0; (unsigned)i < tempArr1.size(); i++)
            cout << tempArr1[i].value << "," << tempArr1[i].index << ";" << endl;;
    //
}//end merge_sort

void SortAlg::merge_sort(vector<Item> & arr1, vector<Item> & arr2, int left, int right){
    if(left < right){
        int center = (left + right) / 2;
        merge_sort(arr1, arr2, left, center);//merge sort left subtree
        merge_sort(arr1, arr2, center+1, right);//merge_sort right subtree
        merge_(arr1,arr2,left,center+1,right); //merges two subarrays together
    }

}

void SortAlg::merge_(vector<Item> & arr1, vector<Item> & arr2, int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos -1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos +1;

    while(leftPos <= leftEnd && rightPos <= rightEnd){
        if(arr1[leftPos].value <= arr1[rightPos].value){ ///move whichever position is less than
            arr2[tempPos++] = move(arr1[leftPos++]);
        }
        else{
        arr2[tempPos++] = move(arr1[rightPos++]);
        }
    }

    while(leftPos <= leftEnd){ ///exhausted right subarray so add the rest of left array
        arr2[tempPos++] = move(arr1[leftPos++]);
    }

    while(rightPos <= rightEnd){ ///exhausted left subarray so add the rest of right array
        arr2[tempPos++] = move(arr1[rightPos++]);
    }

    for(int i = 0; i < numElements; i++ , --rightEnd){
        arr1[rightEnd] = move(arr2[rightEnd]);
    }
}

int SortAlg::partition_(std::vector<Item> & v, int left, int right, int pivot){
  /*
  takes an index of an array
  iterates through the array
  compares if index is less than partitionvalue or greater than

  repeat
  */

  while(left <= right){
    while(v[left].value < v[pivot].value){
        left++;
    }

    while(v[right].value > v[pivot].value){
        right++;
    }

    if(v[left].value <= v[right].value){
        swap(v, left, right);
        left++;
        right--;
    }



  }//end while
  return left; //returns the pivot index of recursive call
}//end partition_

void SortAlg::quick_sort(){ //driving function w/ copy string & print functionality
  std::vector<Item> v = this->m_string; //copy over string to leave original m_string alone

    ///print before quick_sort
  cout << "before quick_sort Set is now:------------------------------------------------------------------ " << endl;
         for(int i = 0; (unsigned)i < v.size(); i++)
          cout << v[i].value << "," << v[i].index << ";" << endl;;
  //

  quick_sort(v, 0, v.size() - 1);

  ///print
  cout << "Final Set is now:------------------------------------------------------------------ " << endl;
         for(int i = 0; (unsigned)i < v.size(); i++)
          cout << v[i].value << "," << v[i].index << ";" << endl;;
  //

}//end quick_sort -- driver

void SortAlg::quick_sort(std::vector<Item> & v, int left, int right){ //begin recursive function
  if(left >= right) //base case for recursive function
    return;

  int pivot = (left + right) / 2; //find the midpoint / median for pivot
  int index = partition_(v, left, right);
  quick_sort(v, left, index - 1, pivot);
  quick_sort(v, index, right, pivot);

}//end quick_sort -- recursive part
