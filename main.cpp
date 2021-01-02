#include <iostream>
#include "summary.h"
#include "exceptions.h"
using namespace std;


int main() {

/*
    Staff s;
    Passages p;
    Traffic t;

    try {
        s.addEmployee(1, "Simon Brown", 1987);
        s.addEmployee(2, "Martin Zelent", 1974);
        s.addEmployee(3, "Ann Rasmus", 1990);
        s.addEmployee(4, "Marta Fischer", 1991);
        s.addEmployee(5, "Simon Brown", 1998);
        s.addEmployee(67, "Ivor Jackson", 1997);
        s.addEmployee(6, "Derek Armstrong", 1985);
        s.addEmployee(7, "Sharon Snee", 1979);
        s.addEmployee(8, "Sarah Carlson", 1979);
        s.addEmployee(9, "Thea Mendez", 1985);
        s.addEmployee(10, "Sarah Carlson", 1985);
        s.addEmployee(11, "Garrick Sutton", 1960);


        s.deleteEmployee(11);
        s.deleteEmployee(67);

        cout << s;
        cout << endl << endl;


        p.addToll("tollA_porto", 41.0954, "N", 8.3845, "W", "entrance");
        p.addToll("tollB_porto", 41.0952, "N", 8.3815, "W", "exit");
        p.addToll("tollA_lisbon", 38.4322, "N", 9.1028, "W", "entrance");
        p.addToll("tollB_lisbon", 38.4323, "N", 9.1001, "W", "exit");
        p.addToll("tollA_coimbra", 40.1253, "N", 8.2641, "W", "entrance");
        p.addToll("tollB_coimbra", 40.1226, "N", 8.2650, "W", "exit");


        GreenLane gl1(315.0);
        GreenLane gl2(315.0);
        NormalLane nl1(315.0);
        NormalLane nl2(315.0);

        GreenLane gl3(317.5);
        GreenLane gl4(317.5);
        NormalLane nl3(317.5);
        NormalLane nl4(317.5);

        GreenLane gl5(125.0);
        GreenLane gl6(125.0);
        NormalLane nl5(125.0);

        GreenLane gl7(204.3);
        GreenLane gl8(204.3);
        NormalLane nl6(204.3);
        NormalLane nl7(204.3);
        NormalLane nl8(204.3);


        p.addGreenLane(gl1, "tollA_porto", "tollB_lisbon");
        p.addGreenLane(gl2, "tollA_porto", "tollB_lisbon");
        p.addNormalLane(nl1, "tollA_porto", "tollB_lisbon", 3);
        p.addNormalLane(nl2, "tollA_porto", "tollB_lisbon", 4);

        p.addGreenLane(gl5, "tollA_porto", "tollB_coimbra");
        p.addGreenLane(gl6, "tollA_porto", "tollB_coimbra");
        p.addNormalLane(nl5, "tollA_porto", "tollB_coimbra", 1);

        p.addGreenLane(gl7, "tollA_coimbra", "tollB_lisbon");
        p.addGreenLane(gl8, "tollA_coimbra", "tollB_lisbon");
        p.addNormalLane(nl6, "tollA_coimbra", "tollB_lisbon", 8);
        p.addNormalLane(nl7, "tollA_coimbra", "tollB_lisbon", 5);
        p.addNormalLane(nl8, "tollA_coimbra", "tollB_lisbon", 6);

        p.addGreenLane(gl3, "tollA_lisbon", "tollB_porto");
        p.addGreenLane(gl4, "tollA_lisbon", "tollB_porto");
        p.addNormalLane(nl3, "tollA_lisbon", "tollB_porto", 7);
        p.addNormalLane(nl4, "tollA_lisbon", "tollB_porto", 9);

        cout << p;
        cout << endl << endl;

        cout << s;
        cout << endl << endl;

        p.changeEmployee(nl1, 2);

        cout << "AFTER SOME CHANGES: " << endl;
        cout << s;
        cout << endl << endl;

        s.sortEmployees("birthyear");
        cout << s;
        cout << endl << endl;

        cout << "FREE:" << endl;
        s.showEmployees("free");
        cout << endl << endl << endl;


        Vehicle motorcycle1("AA 16 AA", 1);
        Vehicle motorcycle2("BE 73 WA", 1);
        Vehicle car1("34 MR 06", 2);
        Vehicle car2("41 BE 81", 2);
        Vehicle truck1("RT 80 12", 3);
        Vehicle truck2("XR 53 42", 3);
        Vehicle bus1("88 90 TH", 4);
        Vehicle bus2("13 67 WE", 4);



        t.enterRoad(car1, "tollA_porto", "tollB_lisbon", "green", 1, 1, 2020);
        t.exitRoad(car1);
        t.enterRoad(car1, "tollA_lisbon", "tollB_porto", "green", 2, 1, 2020);
        t.exitRoad(car1);
        t.enterRoad(bus1, "tollA_porto", "tollB_lisbon", "normal", 3, 1, 2020);
        t.exitRoad(bus1);
        t.enterRoad(motorcycle1, "tollA_porto", "tollB_coimbra", "normal", 2, 2, 2020);
        t.exitRoad(motorcycle1);
        t.enterRoad(car1, "tollA_porto", "tollB_coimbra", "green", 15, 3, 2020);
        t.exitRoad(car1);


        t.enterRoad(motorcycle1, "tollA_porto", "tollB_lisbon", "normal", 18, 11, 2020);
        t.enterRoad(motorcycle2, "tollA_porto", "tollB_lisbon", "normal", 18, 11, 2020);
        t.enterRoad(car1, "tollA_porto", "tollB_lisbon", "green", 18, 11, 2020);
        t.enterRoad(car2, "tollA_porto", "tollB_lisbon", "normal", 18, 11, 2020);
        t.enterRoad(truck1, "tollA_porto", "tollB_lisbon", "green", 18, 11, 2020);
        t.enterRoad(truck2, "tollA_porto", "tollB_lisbon", "normal", 18, 11, 2020);
        t.enterRoad(bus1, "tollA_porto", "tollB_lisbon", "green", 18, 11, 2020);
        t.enterRoad(bus2, "tollA_porto", "tollB_lisbon", "normal", 18, 11, 2020);


        cout << p;
        cout << endl << endl;

        cout << t;
        cout << endl << endl;

        t.sortRidesByDate("desc");
        cout << t;
        cout << endl << endl;

        cout << "RIDES IN JANUARY 2020:" << endl;
        t.ridesBetween(1, 1, 2020, 31, 1, 2020);
        cout << endl << endl;

        cout << "RIDES OF '34 MR 06':" << endl;
        t.showRides("34 MR 06");

    }
    catch(EmployeeAlreadyExists &e)
    {
        cout<<"Caught Exception. Employee already exists: "<<e.getId()<<endl;
    }

    catch(EmployeeDoesNotExist &e)
    {
        cout<<"Caught Exception. Employee does not exist: "<<e.getId()<<endl;
    }

    catch(OccupiedEmployee &e)
    {
        cout<<"Caught Exception. Employee is occupied: "<<e.getId()<<endl;
    }

    catch(TollAlreadyExists &e)
    {
        cout<<"Caught Exception. Toll already exists: "<<e.getName()<<endl;
    }

    catch(TollDoesNotExist &e)
    {
        cout<<"Caught Exception. Toll does not exist: "<<e.getName()<<endl;
    }

    catch(LaneDoesNotExist &e)
    {
        cout<<"Caught Exception. Lane does not exist: "<< e.getStart()<<"-->"<<e.getEnd()<<", type: "<<e.getType()<<endl;
    }

    catch(WrongValue<string> &e)
    {
        cout<<"Caught exception. ";
        e.getInfo();
    }
    catch(WrongValue<float> &e)
    {
        cout<<"Caught exception. ";
        e.getInfo();
    }
    catch(WrongValue<int> &e)
    {
        cout<<"Caught exception. ";
        e.getInfo();
    }

    catch(VehicleDoesNotExist &e)
    {
        cout<<"Caught Exception. Vehicle does not exist: "<<e.getRegistration()<<endl;
    }
*/

    //SECOND PART

    try {

        Staff s;
        Passages p;
        Traffic t;
        Registration r;
        Works w;

        s.addEmployee(1, "Simon Brown", 1987);
        s.addEmployee(2, "Martin Zelent", 1974);
        s.addEmployee(3, "Ann Rasmus", 1990);
        s.addEmployee(4, "Marta Fischer", 1991);
        s.addEmployee(5, "Simon Brown", 1998);
        s.addEmployee(67, "Ivor Jackson", 1997);
        s.addEmployee(6, "Derek Armstrong", 1985);
        s.addEmployee(7, "Sharon Snee", 1979);
        s.addEmployee(8, "Sarah Carlson", 1979);
        s.addEmployee(9, "Thea Mendez", 1985);
        s.addEmployee(10, "Sarah Carlson", 1985);

        p.addToll("tollA_porto", 41.0954, "N", 8.3845, "W", "entrance");
        p.addToll("tollB_porto", 41.0952, "N", 8.3815, "W", "exit");
        p.addToll("tollA_lisbon", 38.4322, "N", 9.1028, "W", "entrance");
        p.addToll("tollB_lisbon", 38.4323, "N", 9.1001, "W", "exit");
        p.addToll("tollA_coimbra", 40.1253, "N", 8.2641, "W", "entrance");
        p.addToll("tollB_coimbra", 40.1226, "N", 8.2650, "W", "exit");

        GreenLane gl1(315.0);
        GreenLane gl2(315.0);
        NormalLane nl1(315.0);
        NormalLane nl2(315.0);

        GreenLane gl3(317.5);
        GreenLane gl4(317.5);
        NormalLane nl3(317.5);
        NormalLane nl4(317.5);

        GreenLane gl5(125.0);
        GreenLane gl6(125.0);
        NormalLane nl5(125.0);

        GreenLane gl7(204.3);
        GreenLane gl8(204.3);
        NormalLane nl6(204.3);
        NormalLane nl7(204.3);
        NormalLane nl8(204.3);


        p.addGreenLane(gl1, "tollA_porto", "tollB_lisbon");
        p.addGreenLane(gl2, "tollA_porto", "tollB_lisbon");
        p.addNormalLane(nl1, "tollA_porto", "tollB_lisbon", 3);
        p.addNormalLane(nl2, "tollA_porto", "tollB_lisbon", 4);

        p.addGreenLane(gl5, "tollA_porto", "tollB_coimbra");
        p.addGreenLane(gl6, "tollA_porto", "tollB_coimbra");
        p.addNormalLane(nl5, "tollA_porto", "tollB_coimbra", 1);

        p.addGreenLane(gl7, "tollA_coimbra", "tollB_lisbon");
        p.addGreenLane(gl8, "tollA_coimbra", "tollB_lisbon");
        p.addNormalLane(nl6, "tollA_coimbra", "tollB_lisbon", 8);
        p.addNormalLane(nl7, "tollA_coimbra", "tollB_lisbon", 5);
        p.addNormalLane(nl8, "tollA_coimbra", "tollB_lisbon", 6);

        p.addGreenLane(gl3, "tollA_lisbon", "tollB_porto");
        p.addGreenLane(gl4, "tollA_lisbon", "tollB_porto");
        p.addNormalLane(nl3, "tollA_lisbon", "tollB_porto", 7);
        p.addNormalLane(nl4, "tollA_lisbon", "tollB_porto", 9);


        Owner o1("Adam Brown", "male", 2003);
        Owner o2("Anne Avonlea", "female", 1985);
        Owner o3("Michael Beckett", "male", 1979);
        Owner o4("Patricia Limanova", "female", 1990);
        Owner o5("Zoe Shrimp", "female", 1979);
        cout << endl << "BEFORE ADDING TO THE SYSTEM" << endl;
        r.showOwners();
        cout << "*****************************************" << endl;

        r.addOwner(o1);
        r.addOwner(o2);
        r.addOwner(o3);
        r.addOwner(o4);
        cout << "AFTER ADDING TO THE SYSTEM" << endl;
        r.showOwners();
        cout << "------------------------" << endl;
        cout << "FILTERED BY SEX" << endl << endl;
        r.filterOwners("sex");
        cout << "*****************************************" << endl;

        Vehicle motorcycle1("AA 78 BB", 1);
        Vehicle car1("AA 78 CB", 2);
        Vehicle car2("CE 15 KK", 2);
        Vehicle car3("CE 19 KA", 2);
        Vehicle truck1("AB 22 AA", 3);
        Vehicle truck2("AC 25 AA", 3);
        Vehicle truck3("DA 29 PO", 3);
        Vehicle truck4("DA 13 KA", 3);
        Vehicle bus1("CE 17 KA", 4);

        //to register a vehicle: owner must be in the system, vehicle cannot have an owner
        r.registerVehicle(o1, motorcycle1);
        r.registerVehicle(o1, car1);
        r.registerVehicle(o2, truck1);
        r.registerVehicle(o2, truck2);
        r.registerVehicle(o3, car2);
        r.registerVehicle(o3, truck3);
        r.registerVehicle(o3, bus1);
        cout << "REGISTERING OF THE VEHICLES" << endl;
        r.showOwners();
        cout << "*****************************************" << endl;

        r.registerVehicle(o4, car3);
        r.registerVehicle(o4, truck4);
        cout << "REGISTERING VEHICLES ON PATRICIA LIMANOVA" << endl;
        cout << o4.write();
        cout << "*****************************************" << endl;

        cout << "LET'S REWRITE PATRICIA'S CAR FOR ANNE:" << endl;

        cout << o4.write();
        cout << o2.write() << "|" << endl << "|" << endl << "V" << endl << endl;
        r.changeOwner(o4, o2, "CE 19 KA");
        cout << o4.write();
        cout << o2.write();
        cout << "*****************************************" << endl;

        cout << "CHANGING OWNER FOR THE PERSON WHO IS NOT YET IN THE RECORD:" << endl;
        cout << "Adam Brown ----> Zoe Shrimp" << endl << endl;
        //we can change owner for the person not registered yet in the system (auto-registration)
        r.changeOwner(o1, o5, "AA 78 BB");
        //o5 appears in the system
        r.showOwners();
        cout << "*****************************************" << endl;

        cout << "ENTERING THE HIGHWAY (TWO DIFFERENT OWNERS):" << endl;
        t.enterRoad(car1, "tollA_porto", "tollB_lisbon", "green", 1, 1, 2020);
        t.exitRoad(car1);
        t.enterRoad(car1, "tollA_porto", "tollB_coimbra", "normal", 3, 1, 2020);
        t.exitRoad(car1);
        r.changeOwner(o1, o5, "AA 78 CB");
        t.enterRoad(car1, "tollA_porto", "tollB_lisbon", "green", 15, 4, 2020);
        t.showRides("AA 78 CB");
        cout << endl << endl;
        cout << "*****************************************" << endl;

        cout << "DELETING THE VEHICLE FROM THE OWNER:" << endl << endl;
        t.enterRoad(car3, "tollA_porto", "tollB_lisbon", "normal", 1, 1, 2020);
        t.exitRoad(car3);
        t.enterRoad(car3, "tollA_porto", "tollB_coimbra", "normal", 18, 11, 2020);
        t.exitRoad(car3);
        r.deleteVehicle(o2, "CE 19 KA");

        cout << "CAR: " << car3.getRegistration() << ", " << car3.getType() << ", owner:" << car3.getOwner() << endl
             << endl;
        cout << "OWNER: " << endl << o2.write();
        cout << "RIDES IN THE DATABASE: " << endl;
        t.showRides("CE 19 KA");
        cout << endl;
        cout << "*****************************************" << endl;

        r.filterOwners("possessions");
        cout << "*****************************************" << endl;

        r.deleteVehicle(o3, "CE 15 KK");
        r.filterOwners("possessions");
        cout << "*****************************************" << endl;

        r.showVehicleTypeOwners(3);
        cout << endl;
        r.showVehicleTypeOwners(1);


        Technician tech1("Militsa Roswitha", "review");
        Technician tech2("Astraia Magda", "review");
        Technician tech3("Lars Bebinn", "electronics");
        Technician tech4("Vasko Anica", "electronics");
        Technician tech5("Kama Yisrael", "informatics");
        Technician tech6("Wesley Phan", "informatics");
        Technician tech7("Tasmin Bowden", "informatics");
        Technician tech8("Rimsha Todd", "review");


        searchToll("tollA_porto")->addTechnician(tech1);
        searchToll("tollA_porto")->addTechnician(tech2);
        searchToll("tollA_porto")->addTechnician(tech3);
        searchToll("tollA_porto")->addTechnician(tech4);
        searchToll("tollA_porto")->addTechnician(tech5);
        searchToll("tollA_coimbra")->addTechnician(tech6);
        searchToll("tollA_coimbra")->addTechnician(tech7);
        searchToll("tollA_coimbra")->addTechnician(tech8);
        //searchToll("tollA_coimbra")->addTechnician(tech8);

        searchToll("tollA_coimbra")->removeTechnician(tech8);

        cout << endl << endl;
        searchToll("tollA_porto")->printTechnicians();
        cout << endl << endl;
        searchToll("tollA_coimbra")->printTechnicians();
        cout << endl << endl;

        w.registerIntervention("review", "tollA_porto", 5, 3, 2020);
        w.startIntervention("review", "tollA_porto", 5, 3, 2020, 7, 3, 2020);
        w.finishIntervention("review", "tollA_porto", 5, 3, 2020, 12, 3, 2020);

        w.registerIntervention("review", "tollA_porto", 20, 3, 2020);
        w.startIntervention("review", "tollA_porto", 20, 3, 2020, 25, 3, 2020);
        w.finishIntervention("review", "tollA_porto", 20, 3, 2020, 27, 3, 2020);

        w.registerIntervention("informatics", "tollA_porto", 28, 3, 2020);
        w.startIntervention("informatics", "tollA_porto", 28, 3, 2020, 20, 3, 2020);
        w.finishIntervention("informatics", "tollA_porto", 28, 3, 2020, 15, 4, 2020);

        w.registerIntervention("informatics", "tollA_coimbra", 3, 3, 2020);
        w.startIntervention("informatics", "tollA_coimbra", 3, 3, 2020, 15, 3, 2020);
        w.finishIntervention("informatics", "tollA_coimbra", 3, 3, 2020, 20, 3, 2020);

        w.registerIntervention("informatics", "tollA_coimbra", 20, 3, 2020);
        w.startIntervention("informatics", "tollA_coimbra", 20, 3, 2020, 20, 3, 2020);
        w.finishIntervention("informatics", "tollA_coimbra", 20, 3, 2020, 22, 3, 2020);

        w.print();
        cout << endl << endl;

        searchToll("tollA_porto")->printTechnicians();
        cout << endl << endl;

        w.registerIntervention("review", "tollA_porto", 1, 1, 2021);
        w.registerIntervention("electronics", "tollA_porto", 2, 1, 2021);
        w.registerIntervention("review", "tollA_coimbra", 3, 1, 2021);

        w.startIntervention("review", "tollA_porto", 1, 1, 2021, 4, 1, 2020);
        w.startIntervention("electronics", "tollA_porto", 2, 1, 2021, 4, 1, 2020);
        w.startIntervention("review", "tollA_coimbra", 3, 1, 2021, 4, 1, 2020);

        cout << endl;
        searchToll("tollA_porto")->printTechnicians();
        cout << endl << endl;

        //w.removeIntervention("review", "tollA_porto", 1, 1, 2021);

        cout << "INTERVENTIONS REGISTERED BETWEEN 01/03/2020 AND 01/04/2020:" << endl;
        w.showInterventionsBetween(1, 3, 2020, 1, 4, 2020);
        cout << endl << endl;

        cout << "INTERVENTIONS REGISTERED BETWEEN 01/03/2020 AND 01/04/2020 ON THE TOLLA_PORTO: " << endl;
        w.showInterventionsBetween(1, 3, 2020, 1, 4, 2020, "tollA_porto");
        cout << endl << endl << endl;

    }

    catch (WrongValue<string> &e) {
            cout << "Caught exception. ";
            e.getInfo();
    }
    catch (WrongValue<unsigned int> &e) {
        cout << "Caught exception. ";
        e.getInfo();
    }
    catch (VehicleAlreadySaved &e) {
        cout << "Caught exception. Vehicle already saved: " << e.getRegistration() << endl;
    }
    catch (OwnerDoesNotExist &e) {
        cout << "Caught exception. Owner does not exist: " << e.getName() << endl;
    }
    catch (VehicleDoesNotExist &e) {
        cout << "Caught exception. Vehicle does not exist: " << e.getRegistration() << endl;
    }
    catch (VehicleWithoutOwner &e) {
        cout << "Caught exception. Vehicle without owner: " << e.getRegistration() << endl;
    }

    catch(TechnicianDoesNotExist &e)
    {
        cout<<"Caught Exception. Technician does not exist in this priority queue: "<<e.getName()<<",speciality: "<<e.getSpeciality()<<endl;
    }

    catch(TechnicianAlreadyExists &e)
    {
        cout<<"Caught Exception. Technician already exists in this priority queue: "<<e.getName()<<", speciality: "<<e.getSpeciality()<<endl;
    }

    catch(InterventionDoesNotExist &e)
    {
        cout<<"Caught Exception. Intervention does not exist: "<<e.write()<<endl;
    }

    catch(InterventionInProgress &e)
    {
        cout<<"Caught Exception. Intervention in progress: "<<e.write()<<endl;
    }
    return 0;
}
