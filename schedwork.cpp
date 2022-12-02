 
 
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"
 
using namespace std;
 
// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;
 
 
// Add prototypes for any helper functions here
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<unsigned int> values);
// Add your implementation of schedule() and other helper functions here
 
bool schedule(
   const AvailabilityMatrix& avail,
   const size_t dailyNeed,
   const size_t maxShifts,
   DailySchedule& sched
)
{
   if(avail.size() == 0U){
       return false;
   }
   sched.clear();
   // Add your code below
 
   std::vector<unsigned int> trackDW; //track days worked
   for(unsigned int i = 0; i <= avail[0].size(); i++){
       trackDW.push_back(0);
   }
   return scheduleHelper(avail, dailyNeed, maxShifts, sched, trackDW);
}
 
bool scheduleHelper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, std::vector<unsigned int> values){

   if(sched.size() == avail.size() && sched[avail.size() - 1].size() == dailyNeed){
       return true; //base case if sizes match and daily requirement met return true for this spot of the matrix
   }
 
   if(sched.size() == 0){ //make sure schedule has at least a day on it
       std::vector<Worker_T> addOne;
       sched.push_back(addOne);
       return scheduleHelper(avail, dailyNeed, maxShifts, sched, values);
   }

	// if((int)sched[avail.size() - 1].size() == (int)dailyNeed && sched[sched.size() - 1].size() == dailyNeed){
	// 		std::vector<Worker_T> addOne;
  //     sched.push_back(addOne);
	// 		return scheduleHelper(avail, dailyNeed, maxShifts, sched, values);
	// }

	// if((int)sched[avail.size() - 1].size() == (int)dailyNeed && sched[sched.size() - 1].size() == dailyNeed){
	// 		std::vector<Worker_T> addOne;
  //     sched.push_back(addOne);
	// 		return scheduleHelper(avail, dailyNeed, maxShifts, sched, values);
	// }

	if(sched[sched.size() - 1].size() == dailyNeed){ //has daily worker requirement been met?
				std::vector<Worker_T> addOne; //if so add another day to schedule
				sched.push_back(addOne);
				return scheduleHelper(avail, dailyNeed, maxShifts, sched, values);
	}

	//workers avail by day
   for(int i = 0; i < (int)avail[0].size(); i++){
       if(avail[sched.size()-1][i] && maxShifts > values[i]){ //if current iteration's worker is available and has not exceeded max number of shifts
           std::vector<unsigned int> updatedValues;
           for(unsigned int i = 0; i < values.size(); i++){ //make deep copy of values vector so we can pass it into recursive function without losing the original list
               updatedValues.push_back(values[i]);
           }
           updatedValues[i] = updatedValues[i] + 1;
           AvailabilityMatrix copyAvail = avail; //make copy of matrix to adjust and recurse on just like the vector while maintaining og values
           sched[sched.size()-1].push_back(i); //schedule worker
           copyAvail[sched.size()-1][i] = false; //mark as false so we know this work spot is no longer available for this worker before passing to recursion
           if(scheduleHelper(copyAvail, dailyNeed, maxShifts, sched, updatedValues) == true){ //check if valid by passing changed vars to recursive function
               return true;
           }
           sched[sched.size()-1].pop_back(); //if previous statement does not work, we need to schedule an alternative by going back
       }
   }

   if(sched[sched.size() - 1].size() == 0){
       sched.pop_back();
   }
   return false; //all else fails and reach end of recursive function then we know schedules not feasible
}
 

