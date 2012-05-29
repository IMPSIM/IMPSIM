package impplugin.editors;

import org.eclipse.swt.graphics.RGB;

/**
 * 
 * @author zastrowm
 *
 */
public interface ColorConstants {
	
	//Color for comments (green)
	RGB COMMENT = new RGB(32, 128, 32);
	
	//Color for keywords (purple)
	RGB KEYWORD = new RGB(128, 32, 64);

	/*************** NOT USED **********************/
	RGB PROC_INSTR = new RGB(128, 128, 128);
	RGB STRING = new RGB(0, 128, 0);
	RGB DEFAULT = new RGB(0, 0, 0);
	RGB S_DATA = new RGB(128,0,0);
	/***********************************************/
}
