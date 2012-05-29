package imp.core.parser;

import imp.core.exceptions.IMPIllegalStateException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.parser.OBJFileFormatException;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Scanner;
/**
 * This class is used for parsing .obj files into the float buffers needed to create the 3D models 
 * in IMP.
 * @author kuszewskij
 *
 */
public class OBJToImpParser {

	/**
	 * This is the string that indicates the following numbers are for defining a face.
	 */
	private final String FACE_START = "f"; 

	/**
	 * This is the string that indicates the following numbers are for defining the location of a vertex.
	 */
	private final String VERTEX_GEO_START = "v";

	/**
	 * This is the string that indicates the following numbers are for defining the normal vector for a vertex
	 */
	private final String VERTEX_NORMAL_START = "vn";

	/**
	 * This is the string that indicates the following numbers are for defining the start of a texture.
	 */
	private final String VERTEX_TEXTURE_START = "vt";

	/**
	 * This is the start of a comment. The rest of the line following this symbol is ignored.
	 */
	private final String COMMENT_START = "#";

	/**
	 * Contains the information representing the object(s) faces.
	 */
	private Integer[] faceBuffer;

	/**
	 * Contains the information representing the normal vectors of the shape(s).
	 */
	private Float[] vertexNormalsBuffer;

	/**
	 * Contains the information representing the textures of the shape(s).
	 */
	private Float[] vertexTextureBuffer;

	/**
	 * Contains the information representing the location of the vectors of the shape(s).
	 */
	private Float[] vertexBuffer;

	/**
	 * This is the name of the file that is currently loaded.
	 */
	private String fileName;
	
	/**
	 * True if a valid file ahs been loaded.
	 */
	private boolean validFileLoaded = false;

	/**
	 * Default constructor for this class. Using this constructor will not initially load a file into the parser.
	 */
	public OBJToImpParser(){

	}

	/**
	 * Creates a parser and parses through the file given as a parameter
	 * @param Filename The file name of the file to parse through
	 * @throws FileNotFoundException throws this exception if the file specified was not found.
	 * @throws IllegalArgumentException throws this exception if there was a problem parsing through the file.
	 * @throws OBJFileFormatException 
	 */
	public OBJToImpParser(String fileName) throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		NullParameterException.check(fileName, "fileName", 0);
		loadFile(fileName);
	}

	/**
	 * This will parse the geographic coordinates out of a line containing vertex geo coordinates.
	 * @param line The line containing the data
	 * @return an ArrayList<Float> containing the data in order.
	 * @throws OBJFileFormatException 
	 */
	private ArrayList<Float> parseVertexGeo(String line) throws OBJFileFormatException{
		ArrayList<Float> verticiesGeo = new ArrayList<Float>();

		int floatCount = 0;//counts the number of floats found for this vertexes coordinates. If there are not 3 or 4 then there is a problem with the file.

		Scanner lineScanner = new Scanner(line);

		String token = lineScanner.next();
		if(token.equals(VERTEX_GEO_START) == false){
			throw new OBJFileFormatException("The line passed in was not a valid line defining a normal: "+line);
		}

		boolean eol = false;
		while(lineScanner.hasNext() && !eol){//go through the entire line.

			token = lineScanner.next();//grab the next part of the line

			if((""+token.charAt(0)).equals(COMMENT_START)){//see if this is the start of a comment.
				break;//if it is then we are done parsing this line.
			}

			//see if there is a comment right next to this token.
			if(token.indexOf(COMMENT_START) > 0 ){
				//strip off the comment if there is one.
				int indexOfCommentStart = token.indexOf(COMMENT_START);
				token = token.substring(0, indexOfCommentStart);
				lineScanner.nextLine();
				eol = true;
			}

			//some floats will be wrapped in []. remove these chars if it is.
			if(token.charAt(0) == '['){
				token = token.substring(1);
			}
			if(token.charAt(token.length()-1) == ']'){
				token = token.substring(0,token.length()-1);
			}

			try{	
				float number = Float.parseFloat(token);//try to get the float value out of the current token.
				verticiesGeo.add(number);//good data. Add it to the list.
				floatCount++;
			}catch(NumberFormatException nfe){
				throw new OBJFileFormatException("There was a problem parsing the value "+token+" in the file "+fileName);
			}
		}

		if(floatCount == 3){//w was not included. add a 1 in place
			verticiesGeo.add(1.0f);
			floatCount++;
		}

		//the entire line has been parsed through. See if enough data has been parsed out to define the vertex.
		if(floatCount != 4){
			//if there wasn't 3 or 4 values parsed out of this line then the data for this vertex is bad.
			throw new OBJFileFormatException("The given file contains bad data for specifying one or more verticies");
		}

		return verticiesGeo;
	}

	/**
	 * This will parse data defining a face out of a given line.
	 * @param line The line containing the data
	 * @return an ArrayList<Integer> containing the data defining the face in order.
	 * @throws OBJFileFormatException 
	 */
	private ArrayList<Integer> parseFace(String line, ArrayList<Float> verticiesGeo) throws OBJFileFormatException{

		Scanner lineScanner = new Scanner(line);

		String token = lineScanner.next();
		if(token.equals(FACE_START) == false){
			throw new OBJFileFormatException("The line passed in was not a valid line defining a face: "+line);
		}

		int numPoints = 0;//the number of points defining the shape on the current line.

		ArrayList<Integer> faces = new ArrayList<Integer>();
		boolean eol = false;
		while(lineScanner.hasNext() && !eol){//go through the entire line.

			token = lineScanner.next();//grab the next part of the line

			if((""+token.charAt(0)).equals(COMMENT_START)){//see if this is the start of a comment.
				break;//if it is then we are done parsing this line.
			}

			//see if there is a comment right next to this token.
			if(token.indexOf(COMMENT_START) > 0 ){
				//strip off the comment if there is one.
				int indexOfCommentStart = token.indexOf(COMMENT_START);
				token = token.substring(0, indexOfCommentStart);
				eol = true;
			}
			try{
				int number = Integer.parseInt(token);//try to parse the index of the vertex thats part of the face.
				number --;
				if(number > (verticiesGeo.size()/4.0)-1|| number < 0){//see if the index is not actually contained in the file.
					throw new OBJFileFormatException("Cannot parse face. The vertex at index "+number+" in the file "+fileName+" does not exist.");
				}else{
					faces.add(number);
					numPoints++;
				}

			}catch(NumberFormatException nfe){
				throw new OBJFileFormatException("There was a problem parsing the value "+token+" in the file "+fileName);
			}
		}

		//the entire line has been parsed through. There should be 3 verticies defining this face.
		if(numPoints != 3){
			if(numPoints == 4){
				//TODO: Not dealing with quads atm. 
			}else{
				//if there aren't 3 vertices then this is a bad file.
				throw new OBJFileFormatException("The given file contains bad data for specifying one or more faces. Data was found specifying a face" +
						"with "+numPoints+" verticies but there should be only 3.");
			}
		}



		return faces;
	}

	/**
	 * This will parse data defining a normal out of a given line.
	 * @param line The line containing the data
	 * @return an ArrayList<Integer> containing the data defining the normal in order.
	 * @throws OBJFileFormatException If the format of the line could not be parsed into normal data.
	 */
	private ArrayList<Float> parseNormal(String line) throws OBJFileFormatException{
		Scanner lineScanner = new Scanner(line);

		String token = lineScanner.next();
		if(token.equals(VERTEX_NORMAL_START) == false){
			throw new OBJFileFormatException("The line passed in was not a valid line defining a normal: "+line);
		}

		int numberOfFloats = 0;//the number of floats found on the current line. There must be 3.

		ArrayList<Float> verticiesNormal = new ArrayList<Float>();
		boolean eol = false;
		while(lineScanner.hasNext() && !eol){//go through the entire line.

			token = lineScanner.next();//grab the next part of the line

			if((""+token.charAt(0)).equals(COMMENT_START)){//see if this is the start of a comment.
				break;//if it is then we are done parsing this line.
			}

			//see if there is a comment right next to this token.
			if(token.indexOf(COMMENT_START) > 0 ){
				//strip off the comment if there is one.
				int indexOfCommentStart = token.indexOf(COMMENT_START);
				token = token.substring(0, indexOfCommentStart);
				lineScanner.nextLine();
				eol = true;
			}
			try{	
				float number = Float.parseFloat(token);//try to get the float value out of the current token.
				verticiesNormal.add(number);//good data. Add it to the list.
				numberOfFloats++;
			}catch(NumberFormatException nfe){
				throw new OBJFileFormatException("There was a problem parsing the value "+token+" in the file "+fileName);
			}
		}

		//After parsing throught the entire line there should be 3 values that were added.
		if(numberOfFloats != 3){
			throw new OBJFileFormatException("The given file contains bad data for one or more normal value. There should be 3 values defining each, but " +
					" there were "+numberOfFloats);
		}

		return verticiesNormal;
	}

	/**
	 * This will parse data defining a texture out of a given line.
	 * @param line The line containing the data
	 * @return an ArrayList<Integer> containing the data defining the normal in order.
	 * @throws OBJFileFormatException If texture data could not be parsed out of the file.
	 */
	private ArrayList<Float> parseTexture(String line) throws OBJFileFormatException{
		Scanner lineScanner = new Scanner(line);
		String token = lineScanner.next();

		if(token.equals(VERTEX_TEXTURE_START) == false){
			throw new OBJFileFormatException("The line passed in was not a valid line defining a texture: "+line);
		}

		int floatCount = 0;//counts the number of floats found for this vertexes coordinates. If there are not 3 or 4 then there is a problem with the file.

		ArrayList<Float> verticiesTexture = new ArrayList<Float>();

		boolean eol = false;
		while(lineScanner.hasNext() && !eol){//go through the entire line.

			token = lineScanner.next();//grab the next part of the line

			if((""+token.charAt(0)).equals(COMMENT_START)){//see if this is the start of a comment.
				break;//if it is then we are done parsing this line.
			}


			//see if there is a comment right next to this token.
			if(token.indexOf(COMMENT_START) > 0 ){
				//strip off the comment if there is one.
				int indexOfCommentStart = token.indexOf(COMMENT_START);
				token = token.substring(0, indexOfCommentStart);
				lineScanner.nextLine();
				eol = true;
			}

			//some floats will be wrapped in []. remove these chars if it is.
			if(token.charAt(0) == '['){
				token = token.substring(1);
			}
			if(token.charAt(token.length()-1) == ']'){
				token = token.substring(0,token.length()-1);
			}

			try{	
				float number = Float.parseFloat(token);//try to get the float value out of the current token.
				verticiesTexture.add(number);//good data. Add it to the list.
				floatCount++;
			}catch(NumberFormatException nfe){
				throw new OBJFileFormatException("There was a problem parsing the value "+token+" in the file "+fileName);
			}
		}

		//the entire line has been parsed through. See if enough data has been parsed out to define the vertex.
		if(floatCount != 2 && floatCount != 3){
			//if there wasn't 2 or 3 values parsed out of this line then the data for this texture is bad.
			throw new OBJFileFormatException("The given file contains bad data for specifying one or more textures");
		}

		return verticiesTexture;
	}

	/**
	 * Calling this method will load the given file into the parser and pull out the information it needs to create 3D IMP models
	 * from the .obj file. The given file must be in obj format. 
	 * @param fileName The name of the obj file.
	 * @throws IllegalArgumentException Will be thrown if the passed in file is not in a valid format.
	 * @throws FileNotFoundException Throws this exception if the file that is specified could not be found.
	 * @throws OBJFileFormatException 
	 */
	public void loadFile(String fileName) throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		faceBuffer = null;
		vertexNormalsBuffer = null;
		vertexTextureBuffer = null;
		vertexBuffer = null;
		
		validFileLoaded = false;
		NullParameterException.check(fileName, "fileName", 0);

		File file = new File(fileName);
		FileReader reader = new FileReader(file);
		Scanner scanner = new Scanner(reader);
		this.fileName = fileName;

		//The next four ArrayLists will be used to dynamically add and hold data as it is parsed out of the file since the number of  faces, vertices, textures .etc
		//is not necessarily known. Each will be converted into float[]s once the entire file has been parsed.
		ArrayList<Integer> faces = new ArrayList<Integer>();//use an ArrayList to hold all of the faces
		ArrayList<Float> verticiesGeo = new ArrayList<Float>();//this ArrayList will hold all of the geographic coordinates of each vertex.
		ArrayList<Float> verticiesNormal = new ArrayList<Float>();//this ArrayList will hold all of the normals for each vertex.
		ArrayList<Float> verticiesTextures = new ArrayList<Float>();//this ArrayList will hold all of the texture data.

		Scanner lineScanner;//used to parse through each individual line.
		String line;//the current line that is being parsed.

		while(scanner.hasNext()){//go through the entire file
			line = scanner.nextLine();
			lineScanner = new Scanner(line);

			String token = "";
			if (lineScanner.hasNext()){
				token = lineScanner.next();//The first part of the line. Defines what the following data represents.
			}

			//the next data is for defining faces
			if(token.equals(FACE_START)){
				faces.addAll(this.parseFace(line, verticiesGeo));
			}

			//the next data is for defining the geographic location of a vertex. (x,y,z[,w]) (w is optional)
			else if(token.equals(VERTEX_GEO_START)){
				verticiesGeo.addAll(this.parseVertexGeo(line));
			}

			//the next data is for defining a normal vector. (x,y,z)
			else if(token.equals(VERTEX_NORMAL_START)){
				verticiesNormal.addAll(this.parseNormal(line));
			}

			//the next data is for defining vertex texture. (u,v,[w,]) (w is optional)
			else if(token.equals(VERTEX_TEXTURE_START)){
				verticiesTextures.addAll(this.parseTexture(line));
			}

			//empty line.
			else if (token.equals("")){
				//do nothing because its an empty line
			}

			//Start of a comment
			else if(token.charAt(0) == '#'){
				//do nothing because this line is commented out.
			}

			//unknown?
			else{
				//not supported yet or unknown.
			}
		}

		//now that all the lines have been gone through, put them into the arrays
		faceBuffer = faces.toArray(new Integer[faces.size()]);
		vertexNormalsBuffer = verticiesNormal.toArray(new Float[verticiesNormal.size()]);
		vertexTextureBuffer = verticiesTextures.toArray(new Float[verticiesTextures.size()]);
		vertexBuffer = verticiesGeo.toArray(new Float[verticiesGeo.size()]);
		
		validFileLoaded = true;
	}

	/**
	 * 
	 * @return Returns the buffer containing the faces for the shape(s). If a file has not been previously loaded, then it will return null.
	 */
	public Integer[] getFaces(){
		if(!validFileLoaded){
			throw new IMPIllegalStateException("A file needs to be loaded first before getting faces.");
		}
		return faceBuffer;
	}

	/**
	 * 
	 * @return Returns the buffer containing the normal vectors for the shape(s). If a file has not been previously loaded, then it will return null.
	 */
	public Float[] getNormals(){
		if(!validFileLoaded){
			throw new IMPIllegalStateException("A file needs to be loaded first before getting Normals.");
		}
		return vertexNormalsBuffer;
	}

	/**
	 * 
	 * @return Returns the buffer containing the textures for the shape(s). If a file has not been previously loaded, then it will return null.
	 */
	public Float[] getTextures(){
		if(!validFileLoaded){
			throw new IMPIllegalStateException("A file needs to be loaded first before getting Textures.");
		}
		return vertexTextureBuffer;
	}

	/**
	 * 
	 * @return Returns the buffer containing the vertices for the shape(s). If a file has not been previously loaded, then it will return null.
	 */
	public Float[] getVertices(){
		if(!validFileLoaded){
			throw new IMPIllegalStateException("A file needs to be loaded first before getting Vertices.");
		}
		return vertexBuffer;
	}

	/**
	 * 
	 * @return Returns the name of the file that is currently loaded.
	 */
	public String getNameOfLoadedFile(){
		if(!validFileLoaded){
			throw new IMPIllegalStateException("A file needs to be loaded first before getting a file name.");
		}
		return fileName;
	}
}
