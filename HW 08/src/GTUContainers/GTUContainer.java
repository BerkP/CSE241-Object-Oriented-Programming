package GTUContainers;

public abstract class GTUContainer<T> {
	
	/**
	 * Test whether container is empty 
	 * @return True if the container is empty
	 */
	public abstract boolean empty();
	
	/**
	 * Return container size
	 * @return container size
	 */
	public abstract int size();
	
	/**
	 * Return maximum size
	 * @return maximum size
	 */
	public abstract int max_size();
	
	/**
	 * Insert element, throws exception java.lang.IllegalArgumentException if there is a problem with insertion
	 * @param value element
	 * @throws IllegalArgumentException if there is a problem with insertion
	 */
	public abstract void insert(T value) throws IllegalArgumentException;
	
	/**
	 * Erase element
	 * @param index index number
	 * @return Erased element
	 * @throws ArrayIndexOutOfBoundsException if index number unvalid
	 */
	public abstract T erase(int index) throws ArrayIndexOutOfBoundsException;
	
	/**
	 * Clear all content 
	 */
	public abstract void clear();
	
	/**
	 * Return iterator to beginning 
	 * @return iterator
	 */
	public abstract GTUIterator<T> iterator();
	
	/**
	 * Returns true if this collection contains the specified element
	 * @param o Element which will be checked
	 * @return True if found!
	 */
	public abstract boolean contains(Object o) ;
	
	
}
