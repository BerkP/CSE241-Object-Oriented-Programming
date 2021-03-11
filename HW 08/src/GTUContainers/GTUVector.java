package GTUContainers;

public class GTUVector<T> extends GTUContainerWithArray<T> {
	
	public GTUVector() {
		this(0);
	}
	
	public GTUVector( int inputSize) {
		super(inputSize);
	}
	
	public GTUVector( GTUVector<T> other) {
		super(other);
	}
	
	public void insert(T value) throws IllegalArgumentException{
		if( size() == max_size()){
			throw new IllegalArgumentException("Max size reached!");
		}
		if(size() == getCapacity()) {
			increaseCapacity(10);
		}
		contArr[size()] = value;
		setSizeOfContainer( size() + 1 );
	}
	
	/**
	 * Insert element to specific index, throws exception java.lang.IllegalArgumentException if there is a problem with insertion
	 * @param value Element to insert
	 * @param index Index number to inserted
	 * @throws IllegalArgumentException if there is a problem with insertion
	 */
	public void insert(T value , int index) throws IllegalArgumentException {
		if( size() == max_size()){
			throw new IllegalArgumentException("Max size reached!");
		}
		
		if(size() == getCapacity()) {
			increaseCapacity(10);
		}
		
		
		for(int i = size()  ; i > index ; i--) {
			contArr[i] = contArr[i-1];
		}
		
		contArr[index] = value;
		setSizeOfContainer(size() + 1);
	}
	
	public boolean equals(Object obj) {
		return super.equals(obj);
	}
	
	public String toString() {
		return super.toString();
	}
	
}
