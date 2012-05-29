package imp.core.parser;

import static org.junit.Assert.*;

import imp.core.exceptions.IMPIllegalStateException;
import imp.core.exceptions.NullParameterException;
import imp.core.exceptions.parser.OBJFileFormatException;

import java.io.FileNotFoundException;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

/**
 * 
 * @author kuszewskij
 *
 */
public class TestOBJToImpParser {

	/**
	 * Used to expect exceptions being thrown during testing.
	 */
	@Rule
	public ExpectedException thrown = ExpectedException.none();

	/**
	 * Test creating a parser with a good file.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testConstructorGoodParams() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		@SuppressWarnings("unused")
		OBJToImpParser otip = new OBJToImpParser("src/test/java/imp/core/parser/GoodFile.obj");
	}

	/**
	 * Test creating a parser with null.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testConstructorNullParams() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		thrown.expect(NullParameterException.class);
		@SuppressWarnings("unused")
		OBJToImpParser otip = new OBJToImpParser(null);
	}

	/**
	 * Test loading a good file.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testLoadingGoodFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile.obj");

		otip.loadFile("src/test/java/imp/core/parser/GoodFile2.obj");

		otip.loadFile("src/test/java/imp/core/parser/GoodFile3.obj");

		otip.loadFile("src/test/java/imp/core/parser/GoodFile5.obj");//human
	}

	/**
	 * Test loading a null file.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testLoadingNullFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(NullParameterException.class);
		otip.loadFile(null);

	}

	/**
	 * Test loading a non existing file.
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 * @throws OBJFileFormatException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testLoadingNonexistingFile() throws FileNotFoundException, NullParameterException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(FileNotFoundException.class);
		otip.loadFile("src/test/java/imp/core/parser/NonExistingFile.obj");
	}

	/**
	 * Test loading a file with bad face data.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testLoadingFileWithBadFaces() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadFaces.obj");
	}

	/**
	 * Test loading a file with bad vertex data.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testLoadingFileWithBadVertices() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadVertices.obj");
	}

	/**
	 * Test loading a file with bad textures.
	 */
	@Test
	public void testLoadingFileWithBadTextures() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadTextures.obj");
	}

	/**
	 * Test loading a file with bad normal data.
	 */
	@Test
	public void testLoadingFileWithBadNormals() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadNormals.obj");
	}

	/**
	 * Test Getting the vertex buffer out of a file with bad vertex data.
	 */
	@Test
	public void testGettingVerticesBadFormat() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadVertices.obj");

	}

	/**
	 * Test Getting the texture buffer out of a file with bad vertex data.
	 */
	@Test
	public void testGettingTexturesBadFormat() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadTextures.obj");
	}

	/**
	 * Test Getting the normal buffer out of a file with bad vertex data.
	 */
	@Test
	public void testGettingNormalsBadFormat() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadNormals.obj");
	}

	/**
	 * Test Getting the faces buffer out of a file with bad vertex data.
	 */
	@Test
	public void testGettingFacesBadFormat() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadFaces.obj");
	}

	/**
	 * Test Getting the vertex buffer out of a good file.
	 */
	@Test
	public void testGettingVerticesGoodFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile3.obj");
		assertEquals(otip.getVertices().length, 32);
	}

	/**
	 * Test loading a valid file with lots of different comments in different places.
	 */
	@Test
	public void testLoadingWithCommentsOnSameLine() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFileComments.obj");
		assertEquals(otip.getVertices().length, 12);
		assertEquals(otip.getNormals().length, 3);
		assertEquals(otip.getFaces().length, 3);
		assertEquals(otip.getTextures().length, 3);
	}

	/**
	 * Test Getting the texture buffer out of a good file.
	 */
	@Test
	public void testGettingTexturesGoodFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile.obj");
		assertEquals(otip.getTextures().length, 12);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile2.obj");//has no textures defined, but still should not crash.
		assertEquals(otip.getTextures().length, 0);
	}

	/**
	 * Test Getting the texture buffer out of a null file.
	 * @throws OBJFileFormatException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingTexturesNullFile() throws FileNotFoundException, NullParameterException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		try{//don't want to use thrown expect because the catch block needs to be run.
			otip.loadFile(null);
		}catch(NullParameterException e){//this should be thrown
			thrown.expect(IMPIllegalStateException.class);
			otip.getTextures();//now try to get textures.
		}
	}

	/**
	 * Test Getting the vertex buffer out of a null file.
	 * @throws OBJFileFormatException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingVerticesNullFile() throws FileNotFoundException, NullParameterException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		try{//don't want to use thrown expect because the catch block needs to be run.
			otip.loadFile(null);
		}catch(NullParameterException e){//this should be thrown
			thrown.expect(IMPIllegalStateException.class);
			otip.getVertices();//now try to get the vertices.
		}
	}

	/**
	 * Test Getting the faces buffer out of a null file.
	 * @throws OBJFileFormatException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingFacesNullFile() throws FileNotFoundException, NullParameterException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		try{//don't want to use thrown expect because the catch block needs to be run.
			otip.loadFile(null);
		}catch(NullParameterException e){//this should be thrown
			thrown.expect(IMPIllegalStateException.class);
			otip.getFaces();//now try to get the vertices.
		}
	}

	/**
	 * Test Getting the normal buffer out of a good file.
	 * @throws OBJFileFormatException 
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingNormalsGoodFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile.obj");
		assertEquals(otip.getNormals().length, 9);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile2.obj");
		assertEquals(otip.getNormals().length, 0);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile3.obj");
		assertEquals(otip.getNormals().length, 0);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile5.obj");//human
		assertEquals(otip.getNormals().length, 0);
	}

	/**
	 * Test Getting the normal buffer out of a null file.
	 * @throws OBJFileFormatException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingNormalsNullFile() throws FileNotFoundException, NullParameterException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		try{//don't want to use thrown expect because the catch block needs to be run.
			otip.loadFile(null);
		}catch(NullParameterException e){//this should be thrown
			thrown.expect(IMPIllegalStateException.class);
			otip.getNormals();//now try to get textures.
		}
	}

	/**
	 * Test Getting the faces buffer out of a good file.
	 */
	@Test
	public void testGettingFacesGoodFile() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile.obj");
		assertEquals(otip.getFaces().length, 12);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile2.obj");
		assertEquals(otip.getFaces().length, 12);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile3.obj");
		assertEquals(otip.getFaces().length, 36);

		otip.loadFile("src/test/java/imp/core/parser/GoodFile5.obj");//human
		assertEquals(otip.getFaces().length, 288);
	}

	/**
	 * Test Getting loading a file that references vertices that do not exist in the face data.
	 */
	@Test
	public void testLoadingFacesBadRefference() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/FileWithBadFaceReferences.obj");
	}

	/**
	 * Test Getting the names of a bunch of different files.
	 * @throws FileNotFoundException 
	 * @throws NullParameterException 
	 */
	@Test
	public void testGettingName() throws NullParameterException, FileNotFoundException, OBJFileFormatException{
		OBJToImpParser otip = new OBJToImpParser();
		otip.loadFile("src/test/java/imp/core/parser/GoodFile.obj");
		assertTrue(otip.getNameOfLoadedFile().equals("src/test/java/imp/core/parser/GoodFile.obj"));

		otip.loadFile("src/test/java/imp/core/parser/GoodFile2.obj");
		assertTrue(otip.getNameOfLoadedFile().equals("src/test/java/imp/core/parser/GoodFile2.obj"));

		otip.loadFile("src/test/java/imp/core/parser/GoodFile3.obj");
		assertTrue(otip.getNameOfLoadedFile().equals("src/test/java/imp/core/parser/GoodFile3.obj"));

		otip.loadFile("src/test/java/imp/core/parser/GoodFile5.obj");//human
		assertTrue(otip.getNameOfLoadedFile().equals("src/test/java/imp/core/parser/GoodFile5.obj"));
		
		thrown.expect(OBJFileFormatException.class);
		otip.loadFile("src/test/java/imp/core/parser/BadNormals.obj");//non file

		thrown.expect(IMPIllegalStateException.class);
		otip.getNameOfLoadedFile();
	}
}
