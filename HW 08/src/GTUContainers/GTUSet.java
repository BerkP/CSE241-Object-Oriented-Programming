package GTUContainers;

public class GTUSet<T> extends GTUContainerWithArray<T> {
	public GTUSet() {
		this(0);
	}
	
	public GTUSet( int inputSize) {
		super(inputSize);
	}
	
	public GTUSet( GTUSet<T> other) {
		super(other);
	}
	
	public void insert(T value) throws IllegalArgumentException{
		if( size() == max_size())
			throw new IllegalArgumentException("Max size reached!");
	
		if ( contains(value))
			throw new IllegalArgumentException("Duplicate element!");
		
		if(size() == getCapacity()) {
			increaseCapacity(10);
		}
		contArr[size()] = value;
		setSizeOfContainer( size() + 1 );
	}
	
	public boolean equals(Object obj) {
		return super.equals(obj);
	}
	
	public String toString() {
		return super.toString();
	}

}
