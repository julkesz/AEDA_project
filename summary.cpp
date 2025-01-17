
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

bool Registration::findOwner(Owner &own)
{
    Owner *pointer = &own;
    tabHOwner::const_iterator it;
    it = owners.find(pointer);
    if(it == owners.end()) return false;
    else return true;
}

void Registration::addOwner(Owner &own)
{
    Owner * pointer = &own;
    if(findOwner(own) == false) owners.insert(pointer);
}

void Registration::registerVehicle(Owner & own, Vehicle &veh)
{
    if(veh.getOwner() != NULL) throw VehicleAlreadySaved(veh.getRegistration());
    Owner * pointer = &own;
    addOwner(own);
    vector<Vehicle *>::const_iterator it;
    vector<Vehicle *> tempvector = own.getMyVehicles();
    for(it = tempvector.begin(); it != tempvector.end(); it++)
    {
        if((*it)->getRegistration() == veh.getRegistration()) throw VehicleAlreadySaved(veh.getRegistration());
    }
    veh.addOwner(pointer);
    Vehicle *vehpointer = &veh;
    own.addVehicle(vehpointer);
}

void Registration::deleteVehicle(Owner & own, string reg)
{
    if(findOwner(own) == false) throw OwnerDoesNotExist(own.getName());
    Owner *pointer = &own;
    Vehicle * vehpointer = NULL;
    for(int i = 0; i != pointer->getMyVehicles().size(); i++)
    {
        if(pointer->getMyVehicles()[i]->getRegistration() == reg)
        {
            vehpointer = pointer->getMyVehicles()[i];
            pointer->removeVehicle(vehpointer);
            vehpointer->deleteOwner();
            break;
        }
    }
    if(vehpointer == NULL) throw VehicleDoesNotExist(reg);
}

void Registration::changeOwner(Owner &oldown, Owner &newown, string reg)
{
    if(findOwner(oldown) == false) throw OwnerDoesNotExist(oldown.getName());
    Owner *pointer = &oldown;
    Vehicle * vehpointer = NULL;
    for(int i = 0; i != pointer->getMyVehicles().size(); i++)
    {
        if(pointer->getMyVehicles()[i]->getRegistration() == reg)
        {
            vehpointer = pointer->getMyVehicles()[i];
            pointer->removeVehicle(vehpointer);
            break;
        }
    }
    if(vehpointer == NULL) throw VehicleDoesNotExist(reg);
    addOwner(newown);
    vehpointer->changeOwner(newown);
    newown.addVehicle(vehpointer);
}

ostream & Registration::showOwners() const
{
    cout << "ALL OWNERS:" << endl << endl;
    if(owners.empty())
    {
        cout << "No owners in database!" << endl << endl;
        return cout;
    }
    tabHOwner::const_iterator it;
    for(it = owners.begin(); it != owners.end(); it++)
    {
        cout << (*it)->write();
    }
    return cout;
}

ostream & Registration::filterOwners(string condition) const
{
    if(condition != "sex" && condition != "possessions") throw WrongValue(condition);
    if(owners.empty())
    {
        cout << "No owners in database!" << endl << endl;
        return cout;
    }
    if(condition == "sex")
    {
        cout << "FEMALES:" << endl << endl;
        tabHOwner::const_iterator it;
        for(it = owners.begin(); it != owners.end(); it++)
        {
            if((*it)->getSex() == "female") cout << (*it)->write();
        }
        cout << "MALES:" << endl << endl;
        for(it = owners.begin(); it != owners.end(); it++)
        {
            if((*it)->getSex() == "male") cout << (*it)->write();
        }
        return cout;
    }
    else
    {
        int maxVehicles = 0;
        tabHOwner::const_iterator it;
        for(it = owners.begin(); it != owners.end(); it++)
        {
            if((*it)->getMyVehicles().size() > maxVehicles) maxVehicles = (*it)->getMyVehicles().size();
        }
        cout << "OWNERS OF THE LARGEST NUMBER OF VEHICLES ("<< maxVehicles <<"): " << endl << endl;
        for(it = owners.begin(); it != owners.end(); it++)
        {
            if((*it)->getMyVehicles().size() == maxVehicles) cout << (*it)->write();
        }
        return cout;
    }
}

ostream & Registration::showVehicleTypeOwners(unsigned int type) const
{
    bool flag = false;
    if(type!= 1 && type!= 2 && type!= 3 && type!= 4) throw WrongValue(type);
    if(owners.empty())
    {
        cout << "No owners in database!" << endl << endl;
        return cout;
    }
    cout << "OWNERS OF THE VEHICLES OF " << type << " TYPE:" << endl << endl;
    tabHOwner::const_iterator it;
    for(it = owners.begin(); it != owners.end(); it++)
    {
        for(int i = 0; i != (*it)->getMyVehicles().size(); i++)
        {
            if((*it)->getMyVehicles()[i]->getType() == type)
            {
                cout << "-->" << (*it)->getName() << endl;
                flag = true;
                break;
            }
        }
    }
    if(flag == false) cout << "No owners!" << endl;
    return cout;
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

Toll* searchToll(string nm){
    vector< Toll *> :: const_iterator it;
    for(it=Passages::tolls_entr.begin(); it!=Passages::tolls_entr.end(); it++)
    {
        if((*it)->getName() == nm) return (*it);
    }

    for(it=Passages::tolls_ex.begin(); it!=Passages::tolls_ex.end(); it++)
    {
        if((*it)->getName() == nm) return (*it);
    }
    throw TollDoesNotExist(nm);
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
    if(vh.getOwner()==NULL) throw VehicleWithoutOwner(vh.getRegistration());

    vector< Toll *> :: const_iterator it1;
    unsigned int pos;

    for(it1=Passages::tolls_entr.begin(); it1!=Passages::tolls_entr.end(); it1++)
    {
        if((*it1)->getName() == toll_s)
        {
            pos=(*it1)->laneMinOccupied(type_chosen, toll_e);
            string own = vh.getOwner()->getName();
            rides.push_back(new Ride(vh,(*it1)->getLanes()[pos-1], pos , d, m, y, own));
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

Works::Works(): interventions(Intervention()){}

BST<Intervention> Works::getInterventions() const{
    return interventions;
}

void Works::registerIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y){
    Toll* toll1 = searchToll(toll_name);
    Intervention intv1(tp, toll1, r_d, r_m, r_y);
    interventions.insert(intv1);
}


bool Works::startIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y, unsigned int s_d, unsigned int s_m, unsigned int s_y){
    Toll* toll1 = searchToll(toll_name);
    Toll t_e = Toll();
    Toll* toll_empty = &t_e;

    Intervention intv = interventions.find(Intervention(tp, toll1, r_d, r_m, r_y));
    Intervention intvNotFound("", toll_empty, 0, 0, 0);

    if (intv==intvNotFound) {
        throw InterventionDoesNotExist(tp, toll1, r_d, r_m, r_y);
    }
    else {
        Technician tech1 = toll1->searchTechnician(intv);

        if(tech1.getName() != "")
        {
            interventions.remove(Intervention(tp, toll1, r_d, r_m, r_y));
            intv.start(tech1, s_d, s_m, s_y);
            interventions.insert(intv);
            return true;

        } else
        {
            cout<<"Intervation: "<< intv.write() << " cannot be started. Suitable technician not found"<<endl;
            return false;
        }

    }
}


bool Works::finishIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y, unsigned int f_d, unsigned int f_m, unsigned int f_y){

    Toll* toll1 = searchToll(toll_name);
    Toll t_e = Toll();
    Toll* toll_empty = &t_e;

    Intervention intv = interventions.find(Intervention(tp, toll1, r_d, r_m, r_y));
    Intervention intvNotFound("", toll_empty, 0, 0, 0);

    if (intv==intvNotFound) {
        throw InterventionDoesNotExist(tp, toll1, r_d, r_m, r_y);
    }
    else {
        interventions.remove(Intervention(tp, toll1, r_d, r_m, r_y));
        intv.finish(f_d, f_m, f_y);
        toll1->addTechnician(intv.getTechnician());
        interventions.insert(intv);
        return true;
    }

}

bool Works::removeIntervention(string tp, string toll_name, unsigned int r_d, unsigned int r_m, unsigned int r_y){
    Toll* toll1 = searchToll(toll_name);
    Toll t_e = Toll();
    Toll* toll_empty = &t_e;

    Intervention intv = interventions.find(Intervention(tp, toll1, r_d, r_m, r_y));
    Intervention intvNotFound("", toll_empty, 0, 0, 0);

    if (intv==intvNotFound) {
        throw InterventionDoesNotExist(tp, toll1, r_d, r_m, r_y);
    }
    else {
        if (intv.getStatus()== "in progress") throw InterventionInProgress(tp, toll1, r_d, r_m, r_y);
        interventions.remove(Intervention(tp, toll1, r_d, r_m, r_y));
        return true;
    }
}

void Works::print() const {
    BSTItrIn<Intervention> it(interventions);
    cout<<"INTERVENTIONS: "<<endl;
    while (!it.isAtEnd()) {
        cout << it.retrieve().write() << endl;
        it.advance();
    }
}


ostream & Works::showInterventionsBetween(unsigned int day1, unsigned int month1, unsigned int year1, unsigned int day2, unsigned int month2, unsigned int year2){
    BSTItrIn<Intervention> it(interventions);
    Toll t_e = Toll();
    Toll* toll_empty = &t_e;
    Intervention intv1("",toll_empty, day1, month1, year1);
    Intervention intv2("",toll_empty, day2, month2, year2);

    while (!it.isAtEnd() && it.retrieve()<intv1) {
        it.advance();
    }

    while (!it.isAtEnd() && it.retrieve()<intv2) {
        cout<<it.retrieve().write()<<endl;
        it.advance();
    }
    return cout;
}


ostream & Works::showInterventionsBetween(unsigned int day1, unsigned int month1, unsigned int year1, unsigned int day2, unsigned int month2, unsigned int year2, string toll_name){
    BSTItrIn<Intervention> it(interventions);
    Toll t_e = Toll();
    Toll* toll_empty = &t_e;
    Intervention intv1("",toll_empty, day1, month1, year1);
    Intervention intv2("",toll_empty, day2, month2, year2);

    while (!it.isAtEnd() && it.retrieve()<intv1) {
        it.advance();
    }

    while (!it.isAtEnd() && it.retrieve()<intv2) {
        if(it.retrieve().getToll()->getName() == toll_name) cout<<it.retrieve().write()<<endl;
        it.advance();
    }
    return cout;
}

