#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
struct Workshop
{
    int start_time, duration, end_time;
    bool operator<(Workshop &w);
};
bool Workshop::operator < (Workshop & w)
{
  if (end_time < w.end_time)
    return true;
  if (end_time == w.end_time && start_time < w.start_time)
    return true;
  return false;
}
struct Available_Workshops
{
    int n=0;
    Workshop *w = new Workshop[n];
};
//Implement the functions initialize and CalculateMaxWorkshops
Available_Workshops* initialize(int start_time[], int duration[], int n)
{
  Available_Workshops *aws = new Available_Workshops();
  aws->n = n;
  for (int i = 0; i < n; i++) {
    aws->w[i].start_time = start_time[i];
    aws->w[i].duration = duration[i];
    aws->w[i].end_time = start_time[i] + duration[i];
  }
  return aws;
}
int CalculateMaxWorkshops(Available_Workshops *ptr)
{
    int m=0;
    int count = ptr->n;
    int endt = 0;
    std::sort(ptr->w, ptr->w + count);
    int* maxes = new int[count];
    int j=0;
    do
    {
      endt = ptr->w[0].end_time;
      m = 1;
      for (int i = 0; i < count; i++) {
        if (endt < ptr->w[i].start_time) {
          endt = ptr->w[i].end_time;
          m++;
        }
        }
        maxes[j] = m;
        j++;
    } while (std::next_permutation(ptr->w, ptr->w + count));
    std::sort(maxes, maxes + count);
    return maxes[count];
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
