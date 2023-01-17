/*
- Project 1
- Noah Beightol
*/


import java.text.DecimalFormat;
import java.util.Scanner;

public abstract class Person {
	//fields
	String name;
	String id;
	public static Student[] arrayStu = new Student[5000];
	public static Faculty[] arrayEmp = new Faculty[5000];
	public static Staff[] arrayStaff = new Staff[5000];

	//constructors
	public Person(String tempName, String tempId) {
		//assigning temp data to new data
		this.name = tempName;
		this.id = tempId;
	}
	//methods
	public abstract void Print();
}



class Student extends Person{
	float gpa;
	int credits;
	final DecimalFormat df = new DecimalFormat("0.00");
	Scanner input = new Scanner(System.in);
	//input.useDelimiter(System.lineSeparator());

	public Student(String tempName, String tempId) {
		super(tempName, tempId);
	}

	public void Print() {
		//declaring all needed variables
		int fee = 52;
		double totalPay;
		double discount = 0.25;
		double tuitionCost;
		double tempTuition = 236.45;
		double subtract = 0.00;

		//checking if student qualifies for discounted tuition
		if(main.arrayStu[main.i].gpa >= 3.85) {
			//calculating tuition
			tuitionCost = (main.arrayStu[main.i].credits * tempTuition);
			subtract =  tuitionCost * discount;
			totalPay = tuitionCost - subtract;
			totalPay = totalPay + fee;
		}
		else {
			totalPay = (main.arrayStu[main.i].credits * tempTuition);
			totalPay = totalPay + fee;
		}
		//displaying invoice
		System.out.println("Here is the tuition invoice for " + main.arrayStu[main.i].name + " :\n\n");
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(main.arrayStu[main.i].name + "            " + main.arrayStu[main.i].id);
		System.out.println("Credit hours: " + main.arrayStu[main.i].credits + " ($236.45/credit hour)");
		System.out.println("Fees: $52\n\n");
		System.out.println("Total payment (after discount): $" + df.format(totalPay) + "         ($" + df.format(subtract) + " discount applied)");
		System.out.println("---------------------------------------------------------------------------\n");
	}

}

abstract class Employee extends Person{

	Scanner input = new Scanner(System.in);
	public Employee(String tempName, String tempId) {
		super(tempName, tempId);
		// TODO Auto-generated constructor stub
	}

	public abstract void Print();


}

class Faculty extends Employee{
	String rank;
	String dept;
	public Faculty(String tempName, String tempId) {
		super(tempName, tempId);
		// TODO Auto-generated constructor stub
	}
	@Override
	//prints out faculty information
	public void Print() {
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(main.capitalize(main.arrayEmp[main.i].name) + "        " + main.arrayEmp[main.i].id);
		System.out.println(main.capitalize(main.arrayEmp[main.i].dept) + " Department, " + main.capitalize(main.arrayEmp[main.i].rank));
		System.out.println("---------------------------------------------------------------------------");
	}

}

class Staff extends Employee{
	String rank;
	String dept;
	String typeOfemp;

	public Staff(String tempName, String tempId) {
		super(tempName, tempId);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void Print() {
		System.out.println("---------------------------------------------------------------------------");
		System.out.println(main.capitalize(main.arrayStaff[main.i].name) + "        " + main.arrayStaff[main.i].id);
		System.out.println(main.capitalize(main.arrayStaff[main.i].dept) + " Department, " + main.capitalize(main.arrayStaff[main.i].typeOfemp));
		System.out.println("---------------------------------------------------------------------------");

	}

}

class main {

	//declaring public variables
	public static Student[] arrayStu = new Student[5000];
	public static Faculty[] arrayEmp = new Faculty[5000];
	public static Staff[] arrayStaff = new Staff[5000];
	public static int i = 0;

	public static void main(String[] args) {
			final DecimalFormat df = new DecimalFormat("0.00");
			Scanner input = new Scanner(System.in);
			input.useDelimiter(System.lineSeparator());

			//declaring needed variables
			int countPeeps = 0;
			int countEmps = 0;
			int countStaff = 0;
			String id;
			String choice = "";
			String name;


			//housekeeping
			System.out.println("						Welcome to my Personal Management Program					");
			System.out.println("Choose one of the options: \n");

			//loop that controls the program
			while(!(choice.equals("7"))) {
				//menu of options
				System.out.println("1- Enter the information of a faculty");
				System.out.println("2- Enter the information of a student");
				System.out.println("3- Print tuition invoice");
				System.out.println("4- Print faculty information");
				System.out.println("5- Enter the information of a staff member");
				System.out.println("6- Print the information of a staff member");
				System.out.println("7- Exit Program");
				System.out.println();

				//taking in users choice
				System.out.print("Enter your selection: ");
				choice = input.next();

				//build faculty
				if(choice.equals("1")) {
					//delaring needed variables
					String tempRank;
					String tempDept;

					//prompting user input
					System.out.println("Enter the faculty info:");
					System.out.print("    Name of the faculty: ");
					name = input.next();

					//taking in user id
					System.out.print("    ID: ");
					id = input.next();

					//creating new employee
					arrayEmp[countEmps] = new Faculty(name, id);

					//taking in the rank of faculty
					System.out.print("    Rank: ");
					tempRank = input.next().toLowerCase();

					//making sure input is valid
					while(!(tempRank.equals("professor") || tempRank.equals("adjunct"))){
						System.out.println("    " + tempRank + " is Invalid");
						System.out.print("    Rank: ");
						tempRank = input.next().toLowerCase();
					}
					//assigning valid input to employee
					arrayEmp[countEmps].rank = tempRank;

					//taking in department
					System.out.print("    Department: ");
					tempDept = input.next().toLowerCase();

					//making sure department is valid
					while(!(tempDept.equals("engineering") || tempDept.equals("mathematics") || tempDept.equals("english"))){
						System.out.println("    " + tempDept + " is Invalid");
						System.out.print("    Department: ");
						tempDept = input.next().toLowerCase();
					}
					//assigning valid input to employee
					arrayEmp[countEmps].dept = tempDept;
					System.out.println("Faculty added!\n");
				}

				//build student
				if(choice.equals("2")) {
					//prompting user input
					System.out.println("Enter the student info:");
					System.out.print("    Name of Student:");
					name = input.next();

					//taking in ID
					System.out.print("    ID: ");
					id = input.next();

					//storing person in array
					arrayStu[countPeeps]= new Student(name, id);

					//taking in GPA
					System.out.print("    Gpa: ");
					arrayStu[countPeeps].gpa = input.nextFloat();

					//taking in Credit hours
					System.out.print("    Credit hours:");
					arrayStu[countPeeps].credits = input.nextInt();

					//final print and updating counter for total people
					System.out.println("Student Added!");
					countPeeps++;
				}

				//tuition
				if(choice.equals("3")) {
					//temp id needed to find id in array
					String tempId;

					//prompting user
					System.out.print("Enter students ID:");
					tempId = input.next();

					//Base case if someone tries to access this command without adding any students to the array
					if(arrayStu[i]== null || arrayStu[i].id == null) {
						System.out.println("No Students matched!");
					}

					//finding user from array
					//inefficient since the i counter must go through 5000 iterations to find something
					else {
						while(!(main.arrayStu[i].id.equals(tempId))) {
							i++;
						}
						if(i > countPeeps) {
							System.out.println("No Students matched!");
						}
						else {
							arrayStu[i].Print();
						}
					}
				}

				//choice 4
				if(choice.equals("4")) {
					//scanning in id
					System.out.print("Enter faculty ID: ");
					String tempId = input.next();


					if(arrayEmp[i]== null || arrayEmp[i].id == null) {
						System.out.println("No Faculty matched!");
					}
					//finding user from array
					//inefficient since the i counter must go through 5000 iterations to find something

					while(!(main.arrayEmp[i].id.equals(tempId))) {
						i++;
						if(i > countPeeps) {
							System.out.println("No Faculty matched!");
							break;
						}

					}
					arrayEmp[i].Print();
				}

				//choice 5
				if(choice.equals("5")) {
					String tempDept;
					String tempEmp;

					System.out.print("Name of staff member: ");
				    name = input.next();

				    System.out.print("Enter the ID: ");
				    id = input.next();

				    arrayStaff[countStaff] = new Staff(name, id);

				    System.out.print("Department: ");
				    tempDept = input.next().toLowerCase();

				    while(!(tempDept.equals("engineering") || tempDept.equals("mathematics") || tempDept.equals("english"))){
						System.out.println(tempDept + " is Invalid");
						System.out.print("Department: ");
						tempDept = input.next().toLowerCase();
					}
				    arrayStaff[countStaff].dept = tempDept;

				    //taking in part or full time
				    System.out.print("Status, Enter P for Part Time, or Enter F for Full Time: " );
				    tempEmp = input.next().toLowerCase();

				    if(tempEmp.equals("p")) {
				    	tempEmp = "Part Time";
				    }
				    if(tempEmp.equals("f")) {
				    	tempEmp = "Full Time";
				    }
				    arrayStaff[countStaff].typeOfemp = tempEmp;
				    System.out.println("\nStaff Member added!\n");

				}

				//choice 6
				if(choice.equals("6")) {
					//scanning in id
					System.out.print("Enter Staff ID: ");
					String tempId = input.next();


					if(arrayStaff[i]== null || arrayStaff[i].id == null) {
						System.out.println("No Staff matched!");
					}
					//finding user from array
					//inefficient since the i counter must go through 5000 iterations to find something

					while(!(main.arrayStaff[i].id.equals(tempId))) {
						i++;
						if(i > countPeeps) {
							System.out.println("No Faculty matched!");
							break;
						}

					}
					arrayStaff[i].Print();
				}

				//choice 7
				if(choice.equals("7")) {
					System.out.println("Goodbye!");
					break;
				}
				//making sure input is valid
				if(!(choice.equals("1") || choice.equals("2") || choice.equals("3") || choice.equals("4") || choice.equals("5") || choice.equals("6") || choice.equals("7") )){
					System.out.println("Invalid Entry- please try again");
				}

			}

		}

	 //capitalize first letter function
		public static String capitalize(String str) {
		    if(str == null || str.isEmpty()) {
		        return str;
		    }

		    return str.substring(0, 1).toUpperCase() + str.substring(1);
	}


	}
