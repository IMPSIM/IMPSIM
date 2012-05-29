package impplugin.editors;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.ui.IViewReference;
import org.eclipse.ui.IWorkbenchPage;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.ide.IDE;
import org.eclipse.ui.texteditor.ITextEditor;

import impplugin.objects.Joints;

public class CodeGenerator {
	
	private CodeGenerator(){}
	
	
	public static void outputJoint(Joints j, IFile myFile)
	{
		
		IWorkbenchPage page = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
		try {
			ITextEditor editor = (ITextEditor) IDE.openEditor(page, myFile);
			myFile.appendContents(new ByteArrayInputStream((j.toString() + "\r\n").getBytes()), true, true, null);
		} catch (PartInitException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void updateJoint(Joints j, int index, IFile myFile)
	{
		IWorkbenchPage page = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage();
		try {
			ITextEditor editor = (ITextEditor) IDE.openEditor(page, myFile);
			myFile.appendContents(new ByteArrayInputStream((j.toString() + "\r\n").getBytes()), true, true, null);
		} catch (PartInitException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
