
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

typedef priority_queue<Technician*> HeapTech;

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
     * adds the lane to the toll
     * @param ln reference to the Lane data type object
     */
    void addLane(Lane &ln);
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

    HeapTech getTechnicians() const;
    unsigned int numberOfTechnicians();
    unsigned addTechnician(Technician* tech1);
    Technician* searchTechnician(Intervention& invt);
    //unsigned fixDefect();

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
    Owner *owner;
public:
    /**
     * Vehicle constructor
     * @param reg vehicle registration
     * @param tp vehicle type (1 or 2 or 3 or 4)
     */
    Vehicle(string reg, int tp, Owner *own);
    ~Vehicle(){};
    /**
     * @return registration of the vehicle
     */
    string getRegistration();
    /**
     * @return the amount of the fee per one kilometer for a given type of vehicle
     */
    float fee();
    Owner * getOwner();
};

class Ride {
    Vehicle *vehicle_assoc;
    Lane *lane_assoc;
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
    Ride(Vehicle &vh, Lane *ln, unsigned int lane_p, unsigned d, unsigned m, unsigned y);
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
    string specialty; //review, electronics or informatics
    vector <Intervention> interventions;
    float time_spent;
public:
    Technician(){};
    Technician(string nm, string spt);
    string getName() const;
    string getSpecialty() const;
    float getPerformance() const;
    void addIntervention(Intervention& intv);
    bool operator<(const Technician& tech1) const;

};

int mkdays(int day, int month, int year);

class Intervention {
    string type;  //review, electronics or informatics
    Toll* toll_assoc; //associated toll
    unsigned int reg_day; //registration day
    unsigned int reg_month; //registration month
    unsigned int reg_year; //registration year
    unsigned int start_day; //start day
    unsigned int start_month; //start month
    unsigned int start_year; //start year
    unsigned int duration; // duration in days
    Technician* technician_resp; //responsible technician
    string status; // "registered" "in progress" "completed"
public:
    Intervention(){};
    Intervention(string tp, Toll* t, unsigned int d, unsigned int m, unsigned int y);
    ~Intervention(){};
    unsigned int getDuration() const;
    string getType() const;
    Technician* getTechnician() const;
    void start(Technician* tech, unsigned int d, unsigned int m, unsigned int y);
    void finish(unsigned int d, unsigned int m, unsigned int y);
    bool operator < (const Intervention &invt1) const;
    bool operator ==(const Intervention &invt1) const;
    string write() const;
};

class Owner{
    string name;
    string sex;     //"male" or "female"
    int birth_year;
    vector<Vehicle *> my_vehicles;
public:
    Owner(string nm, string s, int y);
    ~Owner(){};
    string getName() const;
    bool addVehicle(Vehicle *veh);
    bool removeVehicle(Vehicle *veh);
    vector<Vehicle *> getMyVehicles() const;
    string write() const;
};


#endif //AEDA_PROJECT_HIGHWAY_H
