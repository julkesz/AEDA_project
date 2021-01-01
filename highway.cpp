#include "highway.h"
#include "exceptions.h"


Employee::Employee(unsigned int id, string nm, int y):
    id_number(id), name(nm), birth_year(y)
{status=false;}


unsigned int Employee::getId() const
{
    return id_number;
}

string Employee::getName() const{
    return name;
}

int Employee::getYear() const{
    return birth_year;
}

bool Employee::getStatus() const
{
    return status;
}

void Employee::changeStatus()
{
    if(this->status == false) this->status=true;
    else this->status=false;
}
string Employee::write() const
{
    stringstream os;
    os << id_number << " " << name << ", year of birth: " << birth_year << ", ";
    if(status == true) os << "occupied";
    os << endl;
    return os.str();
}

bool compYear(const Employee &emp1, const Employee &emp2)
{
    return emp1.getYear() < emp2.getYear();
}

Toll::Toll(string nm, float lat_deg, string lat_dir, float long_deg, string long_dir, string dir): name(nm)
{
    if(!(lat_deg>=0 && lat_deg<=90)) throw WrongValue(lat_deg);
    if(!(long_deg>=0 && long_deg<=180)) throw WrongValue(long_deg);
    if(!(lat_dir=="N" || lat_dir=="S")) throw WrongValue(lat_dir);
    if(!(long_dir=="E" || long_dir=="W")) throw WrongValue(long_dir);
    if(!(dir=="entrance" || dir=="exit")) throw WrongValue(dir);

    latitude_deg=lat_deg;
    latitude_dir=lat_dir;
    longitude_deg=long_deg;
    longitude_dir=long_dir;
    direction=dir;
}

string Toll::getName() const {
    return name;
}

string Toll::getLocation() const {
    return to_string(latitude_deg) + " " + latitude_dir + ", " + to_string(longitude_deg) + " " + longitude_dir;
}

vector<Lane *> Toll::getLanes() const {
    return lanes;
}

void Toll::addLane(Lane &ln) {
    Lane * ln_pointer = &ln;
    lanes.push_back(ln_pointer);
}

string Toll::getDirection() const {
    return direction;
}

unsigned int Toll::laneMinOccupied(string type, string toll_end)
{
    vector<Lane *>::const_iterator it;
    vector<Lane *>::const_iterator it2;
    unsigned int min_occ;
    unsigned int counter=0;
    unsigned int min_pos=0;
    for(it=lanes.begin(); it!=lanes.end(); it++)
    {
        counter++;
        if((*it)->getType()== type && (*it)->toll_end==toll_end){
            min_occ = (*it)->occupation;
            min_pos = counter;
            for(it2=it+1; it2!=lanes.end(); it2++)
            {
                counter++;
                if((*it2)->getType()== type && (*it2)->toll_end==toll_end && (*it2)->occupation<min_occ){
                    min_occ = (*it2)->occupation;
                    min_pos = counter;
                }
            } return min_pos;
        }
    } throw LaneDoesNotExist(this->getName(),toll_end, type);
}

ostream & operator <<(ostream &os, const Toll *t){
    os<< t->name<<": "<< endl;
    for(int i=1; i<=t->lanes.size(); i++)
    {
        os << i << " type: " << t->lanes[i-1]->getType() << ", occupation: " << t->lanes[i-1]->getOccupation() <<", ----> "<< t->lanes[i-1]->getTollEnd()<< endl;
    }
    return os;
}


HeapTech Toll::getTechnicians() const{
    return technicians;
}

unsigned int Toll:: numberOfTechnicians(){
    return technicians.size();
}

unsigned Toll::addTechnician(Technician* tech1){
    technicians.push(tech1);
    return technicians.size();
}

Technician* Toll::searchTechnician(Intervention& intv){
    vector<Technician*> temp;

    while (!technicians.empty())
    {
        Technician *tech = technicians.top();
        technicians.pop();
        if (tech->getSpecialty() == intv.getType()) {

            for (unsigned i=0; i<temp.size(); i++)
                technicians.push(temp[i]);
            return tech;
        }
        else temp.push_back(tech);
    }
    for (unsigned i=0; i<temp.size(); i++)
        technicians.push(temp[i]);


    Technician* tech_empty;

    return tech_empty;

}
/*
unsigned Toll::fixDefect(){

}*/






Lane::Lane(float lng):
    length(lng)
{
    occupation=0;
}

float Lane::getLength() const
{
    return length;
}

void Lane::addTolls(string toll_s, string toll_e){
    toll_start = toll_s;
    toll_end = toll_e;
}

string Lane::getTollStart() const
{
    return toll_start;
}

string Lane::getTollEnd() const
{
    return toll_end;
}

unsigned Lane::getOccupation() const{
    return occupation;
}

void Lane::increaseOccupation(){
    occupation++;
}

void Lane::decreaseOccupation(){
    occupation--;
}

GreenLane::GreenLane(float lng):Lane(lng){}

string GreenLane::getType() const{
    return "green";
}

NormalLane::NormalLane(float lng): Lane(lng) {}

string NormalLane::getType() const{
    return "normal";
}

void NormalLane::addEmp(unsigned int id_emp)
{
    id_employee=id_emp;
}

unsigned int NormalLane::getIdEmp() const{
    return id_employee;
}

Vehicle::Vehicle(string reg, int tp, Owner *own):
    registration(reg)
{
    if (tp!=1 && tp!=2 && tp!=3 && tp!=4) throw WrongValue(tp);
    type=tp;
    owner = own;
}

string Vehicle::getRegistration(){
    return registration;
}

float Vehicle::fee()
{
    switch(type)
    {
        case 1: return 0.05f;
        case 2: return 0.1f;
        case 3: return 0.15f;
        case 4: return 0.2f;
        default: return 0;
    }
}

Owner * Vehicle::getOwner()
{
    return owner;
}

void Vehicle::changeOwner(Owner & newown)
{
    owner = &newown;
}

Ride::Ride(Vehicle &vh, Lane *ln, unsigned int lane_p, unsigned d, unsigned m, unsigned y) {
    vehicle_assoc = &vh;
    lane_assoc= ln;
    lane_pos=lane_p;
    day = d;
    month = m;
    year = y;
    present = true;
}

void Ride::end(){
    cost = lane_assoc->getLength() * vehicle_assoc->fee();

    present = false;
    lane_assoc->decreaseOccupation();
}

Vehicle* Ride::getVehicle(){
    return vehicle_assoc;
}

bool Ride::getStatus(){
    return present;
}

float Ride::getCost(){
    return cost;
}

ostream & operator<<(ostream & os, const Ride *r){
    os<< r->lane_assoc->getTollStart() << " --> " << r->lane_assoc->getTollEnd() << ", lane: " << r->lane_pos << " (" << r->lane_assoc->getLength() << "km), date: " << r->day << "/" << r->month<< "/" << r->year << ", vehicle: " << r->vehicle_assoc->getRegistration() << ", cost: ";
    if(r->present == true) os << "...";
    else os << r->cost << " Euro";
    os << endl;
    return os;
}


Technician::Technician(string nm, string spt): name(nm), specialty(spt) {
    time_spent=0;
}


string Technician::getName() const{
    return name;
}

string Technician::getSpecialty() const{
    return specialty;
}

float Technician::getPerformance() const{
    if(interventions.empty()) return 0;
    else return time_spent/interventions.size();
}

void Technician::addIntervention(Intervention& intv){
    interventions.push_back(intv);
    time_spent += intv.getDuration();
}

bool Technician::operator<(const Technician& tech1) const{
    return this->getPerformance() > tech1.getPerformance();
}



static int monthtab[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

int mkdays(int day, int month, int year)
{
    return year*365 + (year-1)/4 - (year-1)/100 + (year-1)/400 + monthtab[month-1] + day-1 + ((month>2 && (year%4 == 0) && (year%100 != 0 || year%400 == 0))?1:0);
}


Intervention:: Intervention(string tp, Toll* t, unsigned int d, unsigned int m, unsigned int y):
    type(tp), toll_assoc(t), reg_day(d), reg_month(m), reg_year(y)
    {duration=0; status="registered";}


unsigned int Intervention::getDuration() const{
    return duration;
}

string Intervention::getType() const{
    return type;
}

Technician* Intervention::getTechnician() const{
    return technician_resp;
}


void Intervention::start(Technician* tech, unsigned int d, unsigned int m, unsigned int y){
    start_day = d;
    start_month = m;
    start_year = y;
    technician_resp= tech;
    status="in progress";
}

void Intervention::finish(unsigned int d, unsigned int m, unsigned int y){
    duration = mkdays(d, m, y) - mkdays(start_day, start_month, start_year);
    status = "completed";
}

bool Intervention:: operator < (const Intervention &invt1) const{
    if (reg_year < invt1.reg_year) return true;
    else if (reg_year > invt1.reg_year) return false;
    else
    {
        if(reg_month < invt1.reg_month) return true;
        else if (reg_month > invt1.reg_month) return false;
        else
        {
            if(reg_day < invt1.reg_day) return true;
            else if (reg_day > invt1.reg_day) return false;
            else
            {
                if(toll_assoc->getName() < invt1.toll_assoc->getName()) return true;
                else if (toll_assoc->getName() > invt1.toll_assoc->getName()) return false;
                else
                {
                    if(type < invt1.type) return true;
                    else return false;
                }
            }
        }
    }
}

bool Intervention:: operator ==(const Intervention &invt1) const{
    return (type == invt1.type && toll_assoc->getName() == invt1.toll_assoc->getName() && reg_day == invt1.reg_day && reg_month==invt1.reg_month && reg_year== invt1.reg_year);
}


string Intervention::write() const
{
    stringstream ss;
    if(status== "registered")
    {
        ss << toll_assoc->getName() << ", type: " << type << ", registration date: "<<reg_day<<"/"<<reg_month<<"/"<<reg_year<<", status: registered";
    }
    else if(status== "in progress")
    {
        ss << toll_assoc->getName() << ", type: " << type << ", registration date: "<<reg_day<<"/"<<reg_month<<"/"<<reg_year<<", technician: "<<technician_resp->getName()<<", status: in progress";
    }
    else
    {
        ss << toll_assoc->getName() << ", type: " << type << ", registration date: "<<reg_day<<"/"<<reg_month<<"/"<<reg_year<<", technician: "<<technician_resp->getName()<<", duration: "<< duration<<" days, status: completed";
    }

    return ss.str();
}

Owner::Owner(string nm, string s, int y)
{
    if(s!="male" && s!="female") throw WrongValue(s);
    else sex=s;
    name=nm;
    birth_year=y;
}

string Owner::getName() const
{
    return name;
}

vector<Vehicle *> Owner::getMyVehicles() const
{
    return my_vehicles;
}

bool Owner::addVehicle(Vehicle *veh)
{
    vector<Vehicle *>::iterator it;
    for(it = my_vehicles.begin(); it != my_vehicles.end(); it++)
    {
        //already added
        if((*it)->getRegistration() == veh->getRegistration()) return false;
    }
    my_vehicles.push_back(veh);
    return true;
}

bool Owner::removeVehicle(Vehicle *veh)
{
    vector<Vehicle *>::iterator it;
    for(it = my_vehicles.begin(); it != my_vehicles.end(); it++)
    {
        if((*it)->getRegistration() == veh->getRegistration())
        {
            it=my_vehicles.erase(it);
            return true;
        }
    }
    return false;
}

string Owner::write() const
{
    stringstream ss;
    ss << "Name: " << name << ", sex: " << sex << ", birth year: " << birth_year << endl;
    if(my_vehicles.empty()) ss << "No vehicles assigned";
    else {
        ss << "Vehicles assigned: " << endl;
        vector<Vehicle *>::const_iterator it;
        for(it=my_vehicles.begin(); it!=my_vehicles.end(); it++)
        {
            ss << (*it)->getRegistration() << endl;
        }
    }
    ss << endl;
    return ss.str();
}