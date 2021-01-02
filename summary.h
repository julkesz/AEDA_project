
#ifndef AEDA_PROJECT_SUMMARY_H
#define AEDA_PROJECT_SUMMARY_H

#include <vector>
#include "highway.h"
#include "bst.h"
#include <unordered_set>

using namespace std;

Toll* searchToll(string nm);

class Staff{
    static inline vector< Employee *> employees;
public:
    /**
     * adds a new employee to the staff
     * @param id identity number of the new employee
     * @param nm name of the new employee
     * @param y year of birth of the new employee
     * @return true if the process was successful
     */
    static bool addEmployee(unsigned id, string nm, int y);
    /**
     * removes the employee from the staff
     * @param id identity number of the employee
     * @return true if the process was successful
     */
    static bool deleteEmployee(unsigned id);
    /**
     * sorts employees in ascending order according to the given condition
     * @param condition the compared feature ("name" or "birthyear")
     */
    void sortEmployees(string condition);
    /**
     * shows occupied or unoccupied (according to the given value) employees in ascending order
     * @param status chosen status of employees ("occupied" or "free")
     * @return ostream data type of the employees (with given status) record
     */
    ostream & showEmployees(string status);
    /**
     * overloads the << operator for Staff data type object
     * @param os output variable
     * @param s reference to Staff data type object
     * @return ostream data type of the employees record
     */
    friend ostream & operator<<(ostream & os, const Staff & s);
    friend class Passages;
};

struct ownerHash
{
    /**
     * hash function used in a case of the hashtable elements conflict
     * @param own pointer to the Owner which will be added to hashtable
     * @return position number of the pointer in hashtable
     */
    int operator() (const Owner* own) const  //hash function (used in case of the conflict)
    {
        string nm = own->getName();
        int v = 0;
        for (unsigned int i = 0; i < nm.size(); i++) v = 37 * v + nm[i];
        return v;
    }

    /**
     * comparing function of hashtable objects
     * @param own1 pointer to the first owner
     * @param own2 pointer to the second owner
     * @return true, if compared objects are identical
     */
    bool operator() (const Owner* own1, const Owner* own2) const   //comparing function
    {
        if(own1->getName() == own2->getName()) return true;
        else return false;
    }
};

typedef unordered_set<Owner*, ownerHash, ownerHash> tabHOwner;

class Registration{
    tabHOwner owners;
public:
    /**
     * checks if the pointer to the owner is already in the owners hashtable
     * @param own reference to the Owner data type object
     * @return true, if the pointer is already in the hashtable
     */
    bool findOwner(Owner & own);
    /**
     * inserts the pointer to the owner to owners hashtable (if there is no)
     * @param own reference to the Owner data type object
     */
    void addOwner(Owner & own);
    /**
     * rewrites the vehicle to the new owner
     * adds the pointer to the new owner to the owners hashtable if he is not there; auto-registration
     * @param oldown reference to the old owner Owner data type object
     * @param newown reference to the new owner Owner data type object
     * @param reg registration of the rewritten vehicle
     */
    void changeOwner(Owner &oldown, Owner &newown, string reg);
    /**
     * removes the vehicle-owner connection
     * @param own reference to the Owner data type object
     * @param reg registration of the vehicle
     */
    void deleteVehicle(Owner & own, string reg);
     /**
      * registers a new vehicle to the owner, adds an owner to the owners hashtable if he is not there
      * @param own reference to the Owner data type object
      * @param veh reference to the Vehicle data type object
      */
    void registerVehicle(Owner & own, Vehicle & veh);  // creating a new Vehicle
    /**
     * shows all owners in the owners hashtable
     * @return ostream data type of the owners (with their assigned vehicles) record
     */
    ostream & showOwners() const;
    /**
     * lists all the owners by gender or shows a partial listing of owners with the largest amount of registered vehicles (according to the given condition)
     * @param condition chosen condition of listing ("sex" or "possessions")
     * @return ostream data type of the owners (according to given condition) record
     */
    ostream & filterOwners(string condition) const;
    /**
     * shows the partial listing of owners, who has at least one vehicle of the given type
     * @param type chosen type of vehicle (1 or 2 or 3 or 4)
     * @return ostream data type of the owners (having at least one vehicle of given type) record
     */
    ostream & showVehicleTypeOwners(unsigned int type) const;
};


class Passages{
    static inline vector<Toll *> tolls_entr;
    static inline vector<Toll *> tolls_ex;
public:
    /**
     * adds a new toll to the passages
     * @param nm name of the toll
     * @param lat_deg location latitude degrees
     * @param lat_dir location latitude direction ("N" or "S")
     * @param long_deg location longitude degrees
     * @param long_dir location longitude direction ("E" or "W")
     * @param dir direction type of the toll ("entrance" or "exit")
     * @return true if the process was successful
     */
    bool addToll (string nm, float lat_deg, string lat_dir, float long_deg, string long_dir, string dir);
    /**
     * adds an existing green lane to the chosen tolls
     * @param gl reference to the Greenlane data type object
     * @param toll_s name of the initial toll
     * @param toll_e name of the final toll
     * @return true if the process was successful
     */
    bool addGreenLane (GreenLane &gl, string toll_s, string toll_e);
    /**
     * adds an existing normal lane to the chosen tolls and assigns the chosen free employee to it
     * @param nl reference to the Normallane data type object
     * @param toll_s name of the initial toll
     * @param toll_e name of the final toll
     * @param id_emp identity number of the free employee
     * @return true if the process was successful
     */
    bool addNormalLane (NormalLane &nl, string toll_s, string toll_e, unsigned int id_emp);
    /**
     * changes employee assigned to the normal lane
     * @param nl reference to the Normallane data type object
     * @param id_new_emp identity number of the free employee
     * @return true if the process was succesful
     */
    bool changeEmployee(NormalLane &nl, unsigned int id_new_emp);
    /**
     * overloads the << operator for Passages data type object
     * @param os output variable
     * @param p reference to the Passages data type object
     * @return ostream data type of the lanes record (with their occupations)
     */
    friend Toll* searchToll(string nm);
    friend ostream & operator<<(ostream & os, const Passages & p);
    friend class Traffic;
};

class Traffic{
    vector< Ride *> rides;
public:
    /**
     * begins a new ride and finds the least occupied lane of the chosen type for the vehicle
     * @param vh  reference to the Vehicle data type object
     * @param toll_s name of the initial toll
     * @param toll_e name of the final toll
     * @param type_chosen type of a lane ("green" or "normal")
     * @param d day of the ride
     * @param m month of the ride
     * @param y year of the ride
     * @return integer position of the lane (starting with one)
     */
    unsigned int enterRoad(Vehicle &vh, string toll_s, string toll_e, string type_chosen, unsigned d, unsigned m, unsigned y);
    /**
     * ends the ride of the vehicle
     * @param vh reference to the Vehicle data type object
     * @return true if the process was successful
     */
    bool exitRoad(Vehicle &vh);
    /**
     * sorts rides by their dates in ascending or descending order (according to given value)
     * @param order chosen order ("asc" or "desc"), the default is "asc"
     */
    void sortRidesByDate(string order = "asc");
    /**
     * shows all rides of the given vehicle in ascending order and counts a total amount paid by the vehicle
     * @param registration of the vehicle
     * @return ostream data type of the rides record and total cost
     */
    ostream & showRides(string registration);
    /**
     * shows all rides between two dates
     * @param day1 day of the first date
     * @param month1 month of the first date
     * @param year1 year of the first date
     * @param day2 day of the second date
     * @param month2 month of the second date
     * @param year2 year of the second date
     * @return ostream data type of the rides record
     */
    ostream & ridesBetween(unsigned day1, unsigned month1, unsigned year1, unsigned day2, unsigned month2, unsigned year2);
    /**
     * overloads the << operator for Traffic data type object
     * @param os output variable
     * @param t reference to Traffic data type object
     * @return ostream data type of the rides record
     */
    friend ostream & operator<<(ostream & os, const Traffic & t);
};



class Works{
    BST<Intervention> interventions;
public:
    Works();
    BST<Intervention> getInterventions() const;
    void addIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y);
    bool startIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y, unsigned int s_d, unsigned int s_m, unsigned int s_y);
    bool finishIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y, unsigned int f_d, unsigned int f_m, unsigned int f_y);
    bool removeIntervention();
    //string searchFor(string word) const;
    void print() const;
};





#endif //AEDA_PROJECT_SUMMARY_H
