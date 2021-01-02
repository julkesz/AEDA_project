
#ifndef AEDA_PROJECT_EXCEPTIONS_H
#define AEDA_PROJECT_EXCEPTIONS_H


class EmployeeAlreadyExists{
    unsigned int id_number;
public:
    EmployeeAlreadyExists(unsigned int id): id_number(id){}
    unsigned int getId() {return id_number;}
};

class EmployeeDoesNotExist{
    unsigned int id_number;
public:
    EmployeeDoesNotExist(unsigned int id): id_number(id){}
    unsigned int getId() {return id_number;}
};

class OccupiedEmployee{
    unsigned int id_number;
public:
    OccupiedEmployee(unsigned int id): id_number(id){}
    unsigned int getId() {return id_number;}
};

class TollAlreadyExists{
    string name;
public:
    TollAlreadyExists(string nm): name(nm){}
    string getName() {return name;}
};

class TollDoesNotExist{
    string name;
public:
    TollDoesNotExist(string nm): name(nm){}
    string getName() {return name;}
};

class LaneDoesNotExist{
    string toll_start;
    string toll_end;
    string type;
public:
    LaneDoesNotExist(string toll_s, string toll_e,string tp):
        toll_start(toll_s), toll_end(toll_e), type(tp){}
    string getStart() {return toll_start;}
    string getEnd(){return toll_end;}
    string getType(){return type;}
};


template<class T>
class WrongValue{
    T name;
public:
    WrongValue(T nm):name(nm){}
    ostream & getInfo()
    {
        cout<< "Wrong Value: "<< name << endl;
        return cout;
    }
};

class VehicleDoesNotExist{
    string registration;
public:
    VehicleDoesNotExist(string reg): registration(reg){}
    string getRegistration() {return registration;}
};


class InterventionDoesNotExist{
    string type;  // review, electronic or computer
    Toll* toll_assoc; //associated toll
    unsigned int reg_day;
    unsigned int reg_month;
    unsigned int reg_year;
public:
    InterventionDoesNotExist(string tp, Toll* t, unsigned int d, unsigned int m,unsigned int y):
    type(tp), toll_assoc(t), reg_day(d), reg_month(m), reg_year(y){}

};


class VehicleAlreadySaved{
    string registration;
public:
    VehicleAlreadySaved(string reg): registration(reg){}
    string getRegistration(){return registration;}
};

class VehicleWithoutOwner{
    string registration;
public:
    VehicleWithoutOwner(string reg): registration(reg){}
    string getRegistration(){return registration;}
};

class OwnerDoesNotExist{
    string name;
public:
    OwnerDoesNotExist(string nm): name(nm){}
    string getName() {return name;}
};


#endif //AEDA_PROJECT_EXCEPTIONS_H
