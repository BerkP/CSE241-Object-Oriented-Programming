package GTUContainers;
import java.util.NoSuchElementException;

public class GTUIterator<T> {
	private T[] iteArr;
	private int counter = 0;
	
	/**
	 * Constructor with parameter
	 * @param inputArr input array of container
	 */
	GTUIterator(T[] inputArr){
		iteArr = inputArr;
	}
	

	/**
	 * Returns the next element in the iteration.
	 * @return the next element in the iteration
	 * @throws NoSuchElementException if the iteration has no more elements
	 */
	public T next() throws NoSuchElementException {
		if ( counter < iteArr.length && iteArr[counter] == null )
			throw new NoSuchElementException();
		return iteArr[counter++];
	}
	
	/**
	 * Returns true if the iteration has more elements. (In other words, returns true if next() would return an element rather than throwing an exception.)
	 * @return true if the iteration has more elements
	 */
	public boolean hasNext() {
		if ( counter < iteArr.length && iteArr[counter] != null )
			return true;
		else
			return false;
	}
}
