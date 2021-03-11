package GTUContainers;

import java.lang.IllegalArgumentException;
import java.lang.ArrayIndexOutOfBoundsException;

public abstract class GTUContainerWithArray<T> extends GTUContainer<T> {

	protected T[] contArr;
	private int sizeOfContainer;
	private int capacity;

	private static final int MAX_SIZE = 1000;

	public abstract void insert(T value) throws IllegalArgumentException;

	/**
	 * No parameter constructor
	 */
	public GTUContainerWithArray() {
		this(0);
	}

	/**
	 * Constructor with size parameter
	 * @param sizeInput size at the beginning
	 */
	public GTUContainerWithArray(int sizeInput) {
		contArr = null;
		if(sizeInput < 1) {
			setSizeOfContainer(0);
			setCapacity(0);
		}
		else {
			increaseCapacity(sizeInput);
			setSizeOfContainer(sizeInput);
			setCapacity(sizeInput);
		}
	}

	/**
	 * Copy constructor
	 * @param other coppied object
	 */
	public GTUContainerWithArray(GTUContainerWithArray<T> other) {
		contArr = null;
		setCapacity(0);
		setSizeOfContainer(0);
		increaseCapacity(other.getCapacity());
		setSizeOfContainer(other.size());
		
		for(int i =  0 ; i < size(); i++) {	
			contArr[i] = other.contArr[i];
		}	
	}
	
	
	/**
	 * Checking equality of two containers
	 */
	@SuppressWarnings("unchecked") // Casting is safe there is no need to check here
	public boolean equals(Object obj) {
		try { 
			GTUContainerWithArray<T> temp = (GTUContainerWithArray<T>) obj;
			if(size() != temp.size())
				return false;
			for (int i = 0; i < size(); i++) {
				if(!contArr[i].equals(temp.contArr[i]))
					return false;
			}
			return true;
		}
		catch(Exception e){
			return false;
		}
	}
	
	
	@SuppressWarnings("unchecked") // Casting is safe there is no need to check here
	public boolean contains(Object o) {
		try {
			T inputElement = (T) o;
			for(int i =  0 ; i < size(); i++) {
				if( contArr[i].equals(inputElement))
					return true;
			}
			return false;
		}
		catch(Exception e ) {
			return false;
		}
	}

	public T erase(int index) throws ArrayIndexOutOfBoundsException {
		if(index < 0 || index >= size() )
			throw new ArrayIndexOutOfBoundsException("Index is out of bound");
		
		T returnElement = contArr[index];
		for(int i = index ; i < size()-1 ; i++) {
			contArr[i] = contArr[i+1];
		}
		contArr[size()-1] = null;
		setSizeOfContainer(size() - 1);
		
		return returnElement;
	}
	
	/**
	 * Increases capacity of the container
	 * @param inputCapacity size for increase
	 */
	@SuppressWarnings("unchecked") // Casting is safe there is no need to check here
	protected void increaseCapacity(int inputCapacity) {
		T[] newContArr = (T[]) new Object[getCapacity() + inputCapacity];
		for (int i = 0; i < size(); i++) {
			newContArr[i] = contArr[i];
		}
		setCapacity(getCapacity() + inputCapacity);
		contArr = newContArr;
	}
	
	/**
	 * Convert container to string
	 */
	public String toString() {
		String str = new String("");
		for (int i = 0; i < size(); i++) {
			str = str + contArr[i].toString() + " ";
		}
		return str;
	}

	public void clear() {
		contArr = null;
		setCapacity(0);
		setSizeOfContainer(0);
	}

	public boolean empty() {
		if (size() == 0)
			return true;
		else
			return false;
	}

	public GTUIterator<T> iterator() {
		GTUIterator<T> newIte = new GTUIterator<T>(contArr);
		return newIte;
	}

	public int size() {
		return sizeOfContainer;
	}

	protected void setSizeOfContainer(int sizeOfContainer) {
		this.sizeOfContainer = sizeOfContainer;
	}

	public int max_size() {
		return MAX_SIZE;
	}

	public int getCapacity() {
		return capacity;
	}

	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}

}
