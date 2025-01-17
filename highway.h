
#ifndef AEDA_PROJECT_HIGHWAY_H
#define AEDA_PROJECT_HIGHWAY_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <queue>
#include <stack>


using namespace std;

class Technician;
class Intervention;
class Lane;
class Owner;

typedef priority_queue<Technician> HeapTech;

class Employee{
    unsigned int id_number;
    string name;
    int birth_year;
    bool status;
public:
    /**
     * Employee constructor, creates unoccupied employee
     * @param id identity number of the employee
     * @param nm name of the employee
     * @param y year of the employee's birth
     */
    Employee(unsigned int id, string nm, int y);
    ~Employee(){};
    /**
     * @return identity number of the employee
     */
    unsigned int getId() const;
    /**
     * @return name of the employee
     */
    string getName() const;
    /**
     * @return year of birth
     */
    int getYear() const;
    /**
     * @return boolean status value of the employee (true when occupied)
     */
    bool getStatus() const;
    /**
     * changes the boolean status value of the employee to the opposite
     */
    void changeStatus();
    /**
     * @return string data type of information about the employee
     */
    string write() const;
    /**
    * compares two employees firstly by their names, secondly by their birth years
    * @param emp1 pointer to the first employee
    * @param emp2 pointer to the second employee
    * @return  true if the name of the first employee is before of the second one.
    * If they have the same names then function returns true if the first employee is older than the second one
    */
    friend bool compName(Employee *emp1, Employee *emp2);
    /**
    * compares two employees firstly by their birth years, secondly by their names
    * @param emp1 pointer to the first employee
    * @param emp2 pointer to the second employee
    * @return  true if the first employee is older than the second one.
    * If they are in the same age then function returns true if the name of the first employee is before of the second one.
    */
    friend bool compYear(Employee *emp1, Employee *emp2);
};


class Toll {
    string name;
    float latitude_deg;
    string latitude_dir;
    float longitude_deg;
    string longitude_dir;
    string direction;
    vector<Lane *> lanes;
    HeapTech technicians;
public:
    /**
    * Empty Toll constructor
    */
    Toll(){};
    /**
     * Toll constructor
     * @param nm name of the toll
     * @param lat_deg location latitude degrees
     * @param lat_dir location latitude direction ("N" or "S")
     * @param long_deg location longitude degrees
     * @param long_dir location longitude direction ("E" or "W")
     * @param dir direction type of the toll ("entrance" or "exit")
     */
    Toll(string nm, float lat_deg, string lat_dir, float long_deg, string long_dir, string dir);
    /**
     * Toll destructor
     */
    ~Toll(){};
    /**
     * @return name of the toll
     */
    string getName() const;
    /**
     * @return location of the toll
     */
    string getLocation() const;
    /**
     * @return vector of pointers to lanes assigned to the toll
     */
    vector <Lane *> getLanes() const;
    /**
     * @return direction type of the toll
     */
    string getDirection() const;
    /**
    * @return priority queue of technicians assigned to the toll
    */
    HeapTech getTechnicians() const;
    /**
     * @return number of technicians assigned to the toll
     */
    unsigned int getNumberOfTechnicians();
    /**
     * adds the lane to the toll
     * @param ln reference to the Lane data type object
     */
    void addLane(Lane &ln);
    /**
     * adds the technician to the toll's priority queue
     * @param tech1 Technician data type object
     */
    void addTechnician(Technician tech1);
    /**
     * removes the technician from the toll's priority queue
     * @param tech1 reference to the Technician data type object
     */
    void removeTechnician(Technician& tech1);
    /**
     * searches for a suitable technician for the intervention (with the highest performance in the required specialty)
     * @param invt reference to the Intervention data type object
     * @return Technician data type object
     */
    Technician searchTechnician(Intervention& invt);
    /**
     * prints list of technicians in the toll's priority queue
     */
    void printTechnicians();
    /**
     * finds the least occupied toll lane of given type
     * @param type chosen type of the lane ("green" or "normal")
     * @param toll_end name of the chosen destination toll
     * @return position of the least occupied lane, starting with 1
     */
    unsigned int laneMinOccupied(string type, string toll_end);
    /**
    * overloads the << operator for pointers to Toll data type objects
    * @param os output variable
    * @param t pointer to Toll data type object
    * @return ostream data type of the toll's lanes record
    */
    friend ostream & operator<<(ostream & os, const Toll * t);
};



class Lane {
protected:
    float length;
    unsigned occupation;
    string toll_start;
    string toll_end;
public:
    /**
     * Lane constructor, creates unoccupied lane
     * @param lng length of the lane [km]
     */
    Lane(float lng);
    virtual ~Lane(){};
    /**
     * @return length of the lane
     */
    float getLength() const;
    /**
     * assigns names of two tolls (start and end) to the Lane data type object attributes
     * @param toll_s name of the initial toll
     * @param toll_e name of the final toll
     */
    void addTolls(string toll_s, string toll_e);
    /**
     * @return name of the initial toll
     */
    string getTollStart() const;
    /**
     * @return name of the final toll
     */
    string getTollEnd() const;
    virtual string getType() const{return "";};
    /**
     * @return actual number of vehicles on the lane
     */
    unsigned getOccupation() const;
    /**
     * increases the occupation number by one
     */
    void increaseOccupation();
    /**
     * reduces the occupation number by one
     */
    void decreaseOccupation();
    friend class Toll;
};

class GreenLane:public Lane{
public:
    /**
     * GreenLane constructor, creates unoccupied green lane
     * @param lng length of the green lane [km]
     */
    GreenLane(float lng);
    /**
     * @return "green"
     */
    string getType() const;
};

class NormalLane:public Lane{
    unsigned int id_employee;
public:
    /**
     * NormalLane constructor, creates unoccupied normal lane
     * @param lng length of the normal lane [km]
     */
    NormalLane(float lng);
    /**
     * @return "normal"
     */
    string getType() const;
    /**
     * @return identity number of the associated employee
     */
    unsigned int getIdEmp() const;
    /**
     * assigns identity number of the employee to the NormalLane data type object attribute
     * @param id_emp identity number of the employee
     */
    void addEmp(unsigned int id_emp);
};

class  Vehicle {
    string registration;
    int type;
    Owner * owner;
public:
    /**
     * Vehicle constructor
     * @param reg vehicle registration
     * @param tp vehicle type (1 or 2 or 3 or 4)
     */
    Vehicle(string reg, int tp);
    ~Vehicle(){};
    /**
     * @return registration of the vehicle
     */
    string getRegistration();
    /**
     * @return type of the vehicle
     */
    unsigned int getType();
    /**
     * @return the amount of the fee per one kilometer for a given type of vehicle
     */
    float fee();
    /**
     * @return pointer to the owner of the vehicle
     */
    Owner * getOwner();
    /**
     * assigns a new owner to the vehicle
     * @param newown pointer to the Owner data type object
     */
    void addOwner(Owner *own);
    /**
     * changes owner for the new one
     * @param newown reference to the Owner data type object
     */
    void changeOwner(Owner & newown);
    /**
     * changes owner attribute for NULL value
     */
    void deleteOwner();
};

class Ride {
    Vehicle *vehicle_assoc;
    Lane *lane_assoc;
    string owner;
    unsigned int lane_pos;
    unsigned day;
    unsigned month;
    unsigned year;
    float cost;
    bool present;
public:
    /**
     * Ride constructor
     * @param vh reference to the Vehicle data type object
     * @param ln pointer to the Lane data type object
     * @param lane_p chosen lane position (starting with one)
     * @param d day of the ride
     * @param m month of the ride
     * @param y year of the ride
     */
    Ride(Vehicle &vh, Lane *ln, unsigned int lane_p, unsigned d, unsigned m, unsigned y, string own);
    ~Ride(){};
    /**
     * @return pointer to the associated vehicle
     */
    Vehicle * getVehicle();
    /**
     * @return true if the vehicle is currently on the highway
     */
    bool getStatus();
    /**
     * @return cost of the ride
     */
    float getCost();
    /**
    * ends the ride and counts its cost
    */
    void end();
    /**
    * overloads the << operator for pointers to Ride data type objects
    * @param os output variable
    * @param r pointer to Ride data type object
    * @return ostream data type of the ride description
    */
    friend ostream & operator<<(ostream & os, const Ride *r);
    /**
     * compares two dates of rides
     * @param r1 pointer to the first ride
     * @param r2 pointer to the second ride
     * @return true if the first ride was before the second one
     */
    friend bool compDate1(Ride *r1, Ride *r2);
    /**
     * compares the given date to the date of the ride
     * @param d1 chosen day
     * @param m1 chosen month
     * @param y1 chosen year
     * @param r pointer to the ride
     * @return true if the given date is earlier than or equal to the date of the ride
     */
    friend bool compDate2(unsigned d1, unsigned m1, unsigned y1, Ride *r);
};



class Technician {
    string name;
    string speciality;
    unsigned int number_of_interventions;
    float time_spent;
public:
    /**
     * Empty Technician constructor
     */
    Technician(){};
    /**
     * Technician destructor
     */
    ~Technician(){};
    /**
     * Technician constructor
     * @param nm name of the technician
     * @param spt speciality of the technician ("review", "electronics" or "informatics")
     */
    Technician(string nm, string spt);
    /**
     * @return name of the technician
     */
    string getName() const;
    /**
     * @return speciality of the technician
     */
    string getSpeciality() const;
    /**
     * @return performance of the technician (the average resolution time of interventions already carried out)
     */
    float getPerformance() const;
    /**
     * increases number of carried out interventions and adds duration of the intervention to the total time spent on interventions
     * @param dur duration of the intervention
     */
    void completeIntervention(unsigned int dur);
    /**
     * compares two technicians
     * @param tech1 reference to the Technician data type object
     * @return true if the second technician has shorter average time of resolving interventions than the first one
     */
    bool operator<(const Technician& tech1) const;
    /**
     * compares two technicians
     * @param tech1 reference to the Technician data type object
     * @return true if the two technicians have the same names and specialities
     */
    bool operator ==(const Technician& tech1) const;
    /**
     * @return string data type of information about the technician
     */
    string write() const;
};


/**
 * counts total number of days from 00/00/0000 to the given date
 * @param day of the date
 * @param month of the date
 * @param year of the date
 * @return number of days
 */
int mkdays(int day, int month, int year);

class Intervention {
    string type;
    Toll* toll_assoc;
    unsigned int reg_day;
    unsigned int reg_month;
    unsigned int reg_year;
    unsigned int start_day;
    unsigned int start_month;
    unsigned int start_year;
    unsigned int duration;
    Technician technician_resp;
    string status; // "registered", "in progress" or "completed"
public:
    /**
     * Empty Intervention constructor
     */
    Intervention(){};
    /**
     * Intervention constructor
     * @param tp type of the intervention ("review", "electronics" or "informatics")
     * @param t pointer to the associated toll
     * @param d day of the intervention's registration
     * @param m month of the intervention's registration
     * @param y year of the intervention's registration
     */
    Intervention(string tp, Toll* t, unsigned int d, unsigned int m, unsigned int y);
    /**
     * Intervention destructor
     */
    ~Intervention(){};
    /**
     * @return pointer to the associated toll
     */
    Toll* getToll() const;
    /**
     * @return duration of the finished intervention (in days)
     */
    unsigned int getDuration() const;
    /**
     * @return type of the intervention ("review", "electronics" or "informatics")
     */
    string getType() const;
    /**
     * @return status of the intervention ("registered", "in progress" or "completed")
     */
    string getStatus() const;
    /**
     * @return technician who resolved/is resolving the intervention
     */
    Technician getTechnician() const;
    /**
     * starts the intervention
     * @param tech reference to the Technician data type object
     * @param d day of the start of the intervention
     * @param m month of the start of the intervention
     * @param y year of the start of the intervention
     */
    void start(Technician& tech, unsigned int d, unsigned int m, unsigned int y);
    /**
     * finishes the intervention
     * @param d day of the end of the intervention
     * @param m month of the end of the intervention
     * @param y year of the end of the intervention
     */
    void finish(unsigned int d, unsigned int m, unsigned int y);
    /**
     * compares two interventions
     * @param invt1 reference to the Intervention data type object
     * @return true if the first intervention was registered before the second one or its toll's name is before the toll's name of the second one or its type is before the type of the second one
     */
    bool operator < (const Intervention& invt1) const;
    /**
     * compares two interventions
     * @param invt1 reference to the Intervention data type object
     * @return true if the two interventions are associated with the same toll and were registered in the same day
     */
    bool operator ==(const Intervention& invt1) const;
    /**
     * @return string data type of information about the intervention
     */
    string write() const;
};



class Owner{
    string name;
    string sex;
    int birth_year;
    vector<Vehicle *> my_vehicles;
public:
    /**
    * Owner constructor, creates an Owner without assigned vehicles
    * @param nm a name of the owner
    * @param s sex of the owner ("male" or "female")
    * @param y year of owner's birth
    */
    Owner(string nm, string s, int y);
    ~Owner(){};
    /**
     * @return name of the owner
     */
    string getName() const;
    /**
     * @return sex of the owner
     */
    string getSex() const;
    /**
     * @return a vector of pointers to owner's vehicles
     */
    vector<Vehicle *> getMyVehicles() const;
    /**
     * adds the vehicle pointer to the owner's my_vehicles vector
     * @param veh pointer to the Vehicle data type object
     * @return false, if vehicle is already assigned to the owner, true, if the process was successful
     */
    bool addVehicle(Vehicle *veh);
    /**
     * removes the vehicle pointer from the owner's my_vehicles vector
     * @param veh pointer to the Vehicle data type object
     * @return false, if there was no such vehicle assigned to the owner, true, if the process was successful
     */
    bool removeVehicle(Vehicle *veh);
    /**
     * @return string data type of information about the owner and his assigned vehicles
     */
    string write() const;
};


#endif //AEDA_PROJECT_HIGHWAY_H
