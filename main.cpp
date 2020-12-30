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


    //SECOND PART

    Works w;


    Technician tech1("Militsa Roswitha", "review");
    Technician tech2("Astraia Magda", "review");
    Technician tech3("Lars Bebinn", "electronics");
    Technician tech4("Vasko Anica", "electronics");
    Technician tech5("Kama Yisrael", "informatics");

    Technician* pointer_tech1 = &tech1;
    Technician* pointer_tech2 = &tech2;
    Technician* pointer_tech3 = &tech3;
    Technician* pointer_tech4 = &tech4;
    Technician* pointer_tech5 = &tech5;

    searchToll("tollA_porto")->addTechnician(pointer_tech1);
    searchToll("tollA_porto")->addTechnician(pointer_tech2);
    searchToll("tollA_porto")->addTechnician(pointer_tech3);
    searchToll("tollA_coimbra")->addTechnician(pointer_tech4);
    searchToll("tollA_coimbra")->addTechnician(pointer_tech5);


    cout<<endl<<endl;
    cout<<searchToll("tollA_porto")->numberOfTechnicians()<<endl;
    cout<<searchToll("tollA_coimbra")->numberOfTechnicians()<<endl;

    w.addIntervention("review","tollA_porto", 5, 3, 2020);
    w.addIntervention("review","tollA_porto", 2, 1, 2018);
    w.addIntervention("informatics","tollA_porto", 5, 3, 2020);
    w.addIntervention("review","tollA_coimbra", 5, 3, 2019);

    w.print();
    cout<<endl<<endl;

    w.startIntervention("review", "tollA_porto", 5, 3, 2020, 7,3,2020);
    w.startIntervention("review", "tollA_porto", 2, 1, 2018, 7,3,2020);
    w.finishIntervention("review", "tollA_porto", 5, 3, 2020, 12,3,2020);
    w.finishIntervention("review", "tollA_porto", 2, 1, 2018, 12,4,2020);
    w.print();

    cout<<endl<<endl;
    cout<<tech1.getPerformance()<<endl;
    cout<<tech2.getPerformance()<<endl;

    */

    /* Julka jest super!! */

    try {
        Registration r;
        cout << "OWNERS:" << endl;
        /*Owner o(1, "Adam Brown", "m", 2003);*/
        Owner o1("Adam Brown", "male", 2003);
        Owner * pointer = &o1;
        cout << o1.write() << endl;
        Vehicle motorcycle1("AA 16 AA", 1, pointer);
        Vehicle motorcycle2("AB 16 AA", 1, pointer);
        o1.addVehicle(&motorcycle1);
        cout << motorcycle1.getOwner()->write();

        Owner o2("Ann Avonlea", "female", 1985);
        Owner o3("Ann Beckett", "female", 1979);
        r.addOwner(o1);
        r.addOwner(o2);
        r.addOwner(o3);
        cout << r.findOwner(o1);
        r.registerVehicle(o1, "AA 78 BB", 2);
        r.registerVehicle(o2, "AB 22 AA", 3);
        /*r.registerVehicle(o2, "AB 22 AA", 3);   naprawić!!*/
    }
    catch(WrongValue<string> &e)
    {
        cout<<"Caught exception. ";
        e.getInfo();
    }

    return 0;
}
