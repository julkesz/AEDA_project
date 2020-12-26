
#include "summary.h"
#include "exceptions.h"

#include <algorithm>


bool Staff::addEmployee(unsigned id, string nm, int y)
{
    vector< Employee *> :: iterator it;
    for(it=employees.begin(); it!=employees.end(); it++)
    {
        if((*it)->getId() == id) throw EmployeeAlreadyExists(id);
    }
    Employee *emp1 = new Employee(id, nm, y);
    employees.push_back(emp1);
    return true;
}

bool Staff::deleteEmployee(unsigned id)
{
    vector< Employee *> :: iterator it;
    for(it=employees.begin(); it!=employees.end(); it++)
    {
        if((*it)->getId() == id && (*it)->getStatus()== false)
        {
            employees.erase(it);
            return true;
        }
    }
    throw EmployeeDoesNotExist(id);
}


bool compName(Employee *emp1, Employee *emp2)
{
    if(emp1->name != emp2->name) return emp1->name < emp2->name;
    else return emp1->birth_year < emp2->birth_year;
}

bool compYear(Employee *emp1, Employee *emp2)
{
    if(emp1->getYear() != emp2->getYear()) return emp1->getYear() < emp2->getYear();
    else return emp1->getName() < emp2->getName();
}

void Staff::sortEmployees(string condition)
{
    if(condition== "name") sort(employees.begin(), employees.end(), compName);
    else if(condition== "birthyear") sort(employees.begin(), employees.end(), compYear);
    else throw WrongValue(condition);
}

ostream & Staff::showEmployees(string status)
{
    bool st;
    if (status== "occupied") st=true;
    else if(status=="free") st=false;
    else throw WrongValue(status);

    sortEmployees("name");

    for (unsigned i=0; i<employees.size(); i++)
    {
        if (employees[i]->getStatus() == st) cout<<employees[i]->write();
    }
    return cout;
}

ostream & operator<<(ostream & os, const Staff & s){
    vector< Employee *>::const_iterator it;
    os<< "STAFF: \n"<<endl;
    for (it = s.employees.begin(); it != s.employees.end(); it++) {
        os<<(*it)->write();
    }
    return os;
}

bool Passages::addToll(string nm, float lat_deg, string lat_dir, float long_deg, string long_dir, string dir) {
    vector< Toll *> :: iterator it;
    if(dir=="entrance")
    {
        for(it=tolls_entr.begin(); it!=tolls_entr.end(); it++)
        {
            if((*it)->getName() == nm) throw TollAlreadyExists(nm);
        }
    }else if(dir=="exit")
    {
        for(it=tolls_ex.begin(); it!=tolls_ex.end(); it++)
        {
            if((*it)->getName() == nm) throw TollAlreadyExists(nm);
        }
    }

    Toll *toll1 = new Toll(nm, lat_deg, lat_dir, long_deg, long_dir, dir);
    if (dir=="entrance") tolls_entr.push_back(toll1);
    else tolls_ex.push_back(toll1);
    return true;
}

bool Passages::addGreenLane(GreenLane &gl, string toll_s, string toll_e){
    vector< Toll *> :: const_iterator it1;
    vector< Toll *> :: const_iterator it2;
    for(it1=tolls_entr.begin(); it1!=tolls_entr.end(); it1++)
    {
        if((*it1)->getName() == toll_s)
        {
            for(it2=tolls_ex.begin(); it2!=tolls_ex.end(); it2++)
            {
                if((*it2)->getName() == toll_e){
                    (*it1)->addLane(gl);
                    (*it2)->addLane(gl);
                    gl.addTolls(toll_s, toll_e);
                    return true;
                }
            } throw TollDoesNotExist(toll_e);
        }
    } throw TollDoesNotExist(toll_s);
}


bool Passages::addNormalLane(NormalLane &nl, string toll_s, string toll_e, unsigned int id_emp) {

    vector< Employee *>::const_iterator it;
    bool exists = false;
    for(it=Staff::employees.begin(); it!=Staff::employees.end(); it++){
        if((*it)->getId() == id_emp){
            exists=true;
            if((*it)->getStatus()== false) {
                break;
            } else throw OccupiedEmployee(id_emp);
        }
    }
    if(exists==false) throw EmployeeDoesNotExist(id_emp);

    vector< Toll *> :: const_iterator it1;
    vector< Toll *> :: const_iterator it2;
    for(it1=tolls_entr.begin(); it1!=tolls_entr.end(); it1++)
    {
        if((*it1)->getName() == toll_s)
        {
            for(it2=tolls_ex.begin(); it2!=tolls_ex.end(); it2++)
            {
                if((*it2)->getName() == toll_e){
                    nl.addEmp(id_emp);
                    (*it)->changeStatus();
                    (*it1)->addLane(nl);
                    (*it2)->addLane(nl);
                    nl.addTolls(toll_s, toll_e);
                    return true;
                }
            } throw TollDoesNotExist(toll_e);
        }
    } throw TollDoesNotExist(toll_s);
}

bool Passages::changeEmployee(NormalLane &nl, unsigned int id_new_emp)
{
    vector<Employee *> :: iterator it2;
    for( it2= Staff::employees.begin(); it2!=Staff::employees.end(); it2++)
    {
        if((*it2)->getId() == id_new_emp)
        {
            if((*it2)->getStatus()==false)
            {
                unsigned int id = nl.getIdEmp();
                vector<Employee *>::iterator it3;
                for(it3=Staff::employees.begin(); it3!=Staff::employees.end(); it3++)
                {
                    if((*it3)->getId() == id) (*it3)->changeStatus();
                }
                nl.addEmp(id_new_emp);
                (*it2)->changeStatus();
                return true;
            } else throw OccupiedEmployee(id_new_emp);
        }
    } throw EmployeeDoesNotExist(id_new_emp);
}

ostream & operator<<(ostream & os, const Passages & p)
{
    vector<Toll *>::const_iterator it;
    os<< "ENTRANCE TOLLS: \n"<<endl;
    for(it=p.tolls_entr.begin(); it!=p.tolls_entr.end();it++)
    {
        os << (*it) << endl;
    }
    return os;
}

unsigned int Traffic::enterRoad(Vehicle &vh, string toll_s, string toll_e, string type_chosen, unsigned d, unsigned m, unsigned y){
    if(type_chosen!= "green" && type_chosen!= "normal") throw WrongValue(type_chosen);

    vector< Toll *> :: const_iterator it1;
    unsigned int pos;

    for(it1=Passages::tolls_entr.begin(); it1!=Passages::tolls_entr.end(); it1++)
    {
        if((*it1)->getName() == toll_s)
        {
            pos=(*it1)->laneMinOccupied(type_chosen, toll_e);
            rides.push_back(new Ride(vh,(*it1)->getLanes()[pos-1], pos , d, m, y));
            (*it1)->getLanes()[pos-1]->increaseOccupation();
            return pos;
        }
    } throw TollDoesNotExist(toll_s);
}

bool Traffic::exitRoad(Vehicle &vh){
    Vehicle * vh_pointer=&vh;
    vector<Ride *>::iterator it;
    for(it=rides.begin(); it!=rides.end(); it++)
    {
        if((*it)->getVehicle() == vh_pointer && (*it)->getStatus() == true)
        {
            (*it)->end();
            return true;
        }
    }
    return false;
}

bool compDate1(Ride *r1, Ride *r2)
{
    if (r1->year < r2->year) return true;
    else if (r1->year > r2->year) return false;
    else
    {
        if(r1->month < r2->month) return true;
        else if (r1->month > r2->month) return false;
        else
        {
            if(r1->day < r2->day) return true;
            else return false;
        }
    }
}


bool compDate2(unsigned d1, unsigned m1, unsigned y1, Ride *r)
{
    if (y1 < r->year) return true;
    else if (y1 > r->year) return false;
    else
    {
        if(m1 < r->month) return true;
        else if (m1 > r->month) return false;
        else
        {
            if(d1 <= r->day) return true;
            else return false;
        }
    }
}

void Traffic::sortRidesByDate(string order)
{
    if(order =="asc") sort(rides.begin(), rides.end(), compDate1);
    else if( order =="desc") sort(rides.rbegin(), rides.rend(), compDate1);
    else throw WrongValue(order);
}

ostream & Traffic::showRides(string registration)
{
    if(rides.empty()) throw VehicleDoesNotExist(registration);
    float total=0;
    bool flag = false;
    sortRidesByDate();
    for(int i = 0; i < rides.size(); i++)
    {
        if(rides[i]->getVehicle()->getRegistration() == registration)
        {
            cout << rides[i];
            total += rides[i]->getCost();
            flag = true;
        }
    }
    if(flag == false) throw VehicleDoesNotExist(registration);

    cout << "Total cost: " << total << " Euro";
    return cout;
}

ostream & Traffic::ridesBetween(unsigned day1, unsigned month1, unsigned year1, unsigned day2, unsigned month2, unsigned year2)
{
    if (rides.empty()) return cout;

    sortRidesByDate();
    int i=0;
    while(!(compDate2(day1, month1, year1,rides[i])) && i<rides.size())
    {
        i++;
        if(i== rides.size()) return cout;
    }
    while((!(compDate2(day2+1, month2, year2, rides[i]))) && (i<rides.size()))
    {
        cout << rides[i];
        i++;
        if (i== rides.size()) break;
    }
    return cout;
}


ostream & operator<<(ostream & os, const Traffic & t){
    vector<Ride *>::const_iterator it;
    os<< "RIDES: \n"<<endl;
    for(it=t.rides.begin(); it!=t.rides.end(); it++)
    {
        os << (*it);
    }
    return os;
}

Works::Works(): interventions(Intervention("",Toll(),0,0,0,Technician())){}

BST<Intervention> Works::getInterventions() const{
    return interventions;
}

/*
bool Works::startIntervention(string tp, Toll t, unsigned int d, unsigned int m, unsigned int y){

    Intervention intv1(tp, t, d, m, y, TECHNICIAN);
    interventions.insert(intv1);
}*/

bool Works::finishIntervention(string tp, Toll t, unsigned int d1, unsigned int m1, unsigned int y1, unsigned int d2, unsigned int m2, unsigned int y2){

    Intervention intv = interventions.find(Intervention(tp, t, d1, m1, y1, Technician()));
    Intervention intvNotFound("", Toll(), 0, 0, 0, Technician());

    if (intv==intvNotFound) {
        throw InterventionDoesNotExist(tp, t, d1, m1, y1);
        return false;
    }
    else {
        interventions.remove(Intervention(tp, t, d1, m1, y1, Technician()));
        intv.finish(d2, m2, y2);
        interventions.insert(intv);
        return true;
    }

}

void Works::print() const {
    BSTItrIn<Intervention> it(interventions);
    while (!it.isAtEnd()) {
        cout << it.retrieve().write() << endl;
        it.advance();
    }
}
