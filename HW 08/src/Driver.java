import GTUContainers.*;

public class Driver {

	public static void main(String[] args) {
		try {
			
			
			System.out.println( "*******************************");
			System.out.println( "GTUVector TEST has been started");
			System.out.println( "*******************************");

			GTUVector<Integer> myVec1 = new GTUVector<Integer>();
			System.out.printf( "max_size of a GTUVector  is %d \n" , myVec1.max_size()); 
			
			myVec1.insert(2);
			myVec1.insert(3);
			myVec1.insert(4);
			myVec1.insert(5);
			myVec1.insert(6);
			myVec1.insert(7);
			myVec1.insert(8);
			myVec1.insert(9);
			myVec1.insert(10);

			System.out.println( "<Integer>myVec1 created and inserted 2-3-4-5-6-7-8-9-10 as value" ); 

			System.out.printf( "Current vector: %s \n",myVec1.toString() );
			System.out.printf( "with size: %d \n" , myVec1.size() );

			myVec1.insert(1,0);

			System.out.printf( "Value 1 inserted to index 0\n"); 

			System.out.printf( "Current vector: %s \n",myVec1.toString() );
			System.out.printf( "with size: %d \n" , myVec1.size() );

			
			myVec1.clear();
			myVec1.insert(9);
			myVec1.insert(8,0);
			myVec1.insert(10);
			myVec1.insert(11);

			System.out.println( "clear() called and 9 - 8(with index 0 ) - 10 - 11 inserted in order" ); 

			System.out.printf( "Current vector: %s \n",myVec1.toString() );
			System.out.printf( "with size: %d \n" , myVec1.size() );


			
			myVec1.erase(2);
			System.out.println( "erase() called with index 1 (second element in vector)" ); 

			System.out.printf( "Current vector: %s \n",myVec1.toString() );
			System.out.printf( "with size: %d \n" , myVec1.size() );
			
			GTUIterator<Integer> myIte = myVec1.iterator(); 
			System.out.println( "Iterator myIte created with myVec1.iterator() and next() printed until hasNext() return false" ); 
			while(myIte.hasNext()) {
				System.out.printf("%d ",myIte.next());
			}
			System.out.println(" ");
			
			System.out.printf( "Contains(9) called and result is: " ); 
			if(myVec1.contains(9)) 
				System.out.println("TRUE");
			else
				System.out.println("FALSE");
			
			System.out.printf( "Contains(67) called and result is: " ); 
			if(myVec1.contains(67)) 
				System.out.println("TRUE");
			else
				System.out.println("FALSE");
			


			System.out.println( "For exception test, myVec2 created and insert() called 10001(max_size is 1000) times" ); 
			GTUVector<Integer> myVec2 = new GTUVector<Integer>();
			try{
				for(int i=0 ; i < 1001 ; i++){
					myVec2.insert(i);
				}
			}
			catch(Exception e ){
				System.out.printf( "exception cathed and IllegalArgumentException.getMessage() called : %s \n" , e.getMessage() ); 
			}	

			System.out.printf( "Size of myVec2: %d \n" , myVec2.size() );
			
			
			
			System.out.println( "*******************************");
			System.out.println( "GTUSet TEST has been started");
			System.out.println( "*******************************");

			GTUSet<Integer> mySet1 = new GTUSet<Integer>();
			System.out.printf( "max_size of a GTUSet  is %d \n" , mySet1.max_size()); 
			
			mySet1.insert(2);
			mySet1.insert(3);
			mySet1.insert(4);
			mySet1.insert(5);
			mySet1.insert(6);
			mySet1.insert(7);
			mySet1.insert(8);
			mySet1.insert(9);
			mySet1.insert(10);

			System.out.println( "<Integer>mySet1 created and inserted 2-3-4-5-6-7-8-9-10 as value" ); 

			System.out.printf( "Current set: %s \n",mySet1.toString() );
			System.out.printf( "with size: %d \n" , mySet1.size() );



			
			mySet1.clear();
			mySet1.insert(9);
			mySet1.insert(8);
			mySet1.insert(10);
			mySet1.insert(11);

			System.out.println( "clear() called and 9 - 8 - 10 - 11 inserted in order" ); 

			System.out.printf( "Current set: %s \n",mySet1.toString() );
			System.out.printf( "with size: %d \n" , mySet1.size() );


			
			mySet1.erase(2);
			System.out.println( "erase() called with index 1 (second element in set)" ); 

			System.out.printf( "Current set: %s \n",mySet1.toString() );
			System.out.printf( "with size: %d \n" , mySet1.size() );
			
			myIte = mySet1.iterator(); 
			System.out.println( "Iterator myIte created with mySet1.iterator() and next() printed until hasNext() return false" ); 
			while(myIte.hasNext()) {
				System.out.printf("%d ",myIte.next());
			}
			System.out.println(" ");
			
			System.out.printf( "Contains(9) called and result is: " ); 
			if(mySet1.contains(9)) 
				System.out.println("TRUE");
			else
				System.out.println("FALSE");
			
			System.out.printf( "Contains(67) called and result is: " ); 
			if(mySet1.contains(67)) 
				System.out.println("TRUE");
			else
				System.out.println("FALSE");
			


			System.out.println( "For exception test, mySet2 created and insert() called 10001(max_size is 1000) times" ); 
			GTUSet<Integer> mySet2 = new GTUSet<Integer>();
			try{
				for(int i=0 ; i < 1001 ; i++){
					mySet2.insert(i);
				}
			}
			catch(Exception e ){
				System.out.printf( "exception cathed and IllegalArgumentException.getMessage() called : %s \n" , e.getMessage() ); 
			}	

			System.out.printf( "Size of mySet2: %d \n" , mySet2.size() );
			
		
		}
		
		catch(Exception e) {
			System.out.println("Something went wrong in main!");
		}
	
		
		
	}

}
