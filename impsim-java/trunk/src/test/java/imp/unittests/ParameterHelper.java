package imp.unittests;

public class ParameterHelper {

	/**
	 * Return sets of parameters that each have one null argument
	 * 
	 * @param args the normal arguments
	 * @return an array of arrays that represent each set of arguments, each with the subsequent argument null.
	 * @example returnSingleNullSet("one", "two", "three" would return <code>
	 * 	[null, "two", "three"]
	 * 	["one", null, "three"]
	 * 	["one", "two", null]
	 *  </code>
	 */
	public static Object[] returnSingleNullSet(Object... args) {

		// make a new array to hold everything
		Object[][] argsArray = new Object[args.length][];

		// for each set of arguments
		for (int i = 0; i < args.length; i++) {
			argsArray[i] = new Object[args.length];

			// copy each argument, except for the one that should be null
			for (int j = 0; j < args.length; j++) {
				if (j == i) {
					argsArray[i][j] = null;
				} else {
					argsArray[i][j] = args[j];
				}
			}
		}
		return argsArray;
	}
}
