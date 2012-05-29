package imp.core.graphics;


import java.util.ArrayList;
import java.util.List;

import javax.media.opengl.GL3;

import imp.core.commands.encapsulation.CommandHolder;
import imp.core.commands.encapsulation.JointHolder;
import imp.core.commands.encapsulation.LoopHolder;
import imp.core.observer.NotificationType;
import imp.core.structures.Point;

/**
 * Class used to hold data for drawing basic loops from a command holder
 * @author kreierj
 * @version 1
 */
@Deprecated
public class LoopDataSource extends AbstractDataSource{


	/**
	 * Synchronization tool
	 */
	public Object lock = new String("lock");

	/**
	 * Loop data
	 */
	public List<LoopHolder> data = null;

	/**
	 * CommandHolder object
	 */
	public CommandHolder commandHolder;

	/**
	 * Indicates if the loop has changed since the last update
	 */
	protected boolean hasChanged;

	/**
	 * Constructor which causes the CommandDataSource to observe the command holder
	 * @param ch The command holder to observe
	 */
	public LoopDataSource(CommandHolder ch){
		commandHolder = ch;
		ch.addObserver(this);
		hasChanged = true;
	}

	/**
	 * Refreshes the joint data being drawn
	 */
	protected void refreshJoints(GL3 gl){
		
		synchronized(lock){
			if(hasChanged){
				data = commandHolder.getLoops();

				if (this.getObjects().size() == 0){ //initializing everything
					for (int i = 0; i < data.size(); i++){
						//for each Joint holder
						List<JointHolder> joints = data.get(i).getJoints();
						
						//initialize lists for vertex and color data
						List<Float> loopPath = new ArrayList<Float>(joints.size()*4);
						List<Float> loopColorData = new ArrayList<Float>(joints.size()*4);

						//for each joint
						for(JointHolder jh: joints){

							//get its position
							Point p = jh.getPosition();
							float x = (float)p.getX();
							float y = (float)p.getY();
							float z = (float)p.getZ();

							//add the vertex to the loop path
							loopPath.add(x);
							loopPath.add(y);
							loopPath.add(z);
							loopPath.add(1.0f);

							//add the vertex color to the loop path
							loopColorData.add((float)Math.random());
							loopColorData.add((float)Math.random());
							loopColorData.add((float)Math.random());
							loopColorData.add(1.0f);

						}

						//create the GL Object with a unique name
						AbstractGLObject object = new LoopObject("Loop"+i, loopPath, loopColorData);

						//initialize the object
						object.initialize(gl);

						//add the object to the list of objects to draw
						this.putObject(object);
					}
				}
				else{ //need to update everything
					for (int i = 0; i < data.size(); i++){
						//for each joint holder
						List<JointHolder> joints = data.get(i).getJoints();

						//initialize list for new vertex data
						List<Float> loopPath = new ArrayList<Float>(joints.size()*4);

						//for each joint
						for(JointHolder jh: joints){

							//get the position
							Point p = jh.getPosition();
							float x = (float)p.getX();
							float y = (float)p.getY();
							float z = (float)p.getZ();

							//add the position to the list
							loopPath.add(x);
							loopPath.add(y);
							loopPath.add(z);
							loopPath.add(1.0f);

							
						}

						//get the object from the list
						AbstractGLObject object = this.getObject("Loop"+i);
						
						//update the object
						object.updateData(gl, loopPath, AbstractGLObject.DATA_TYPE.VERTEX_DATA);

						this.removeObject(object.getName());
						
						//put the object back in the list
						this.putObject(object);
					}
				}
			}
			
			
			hasChanged = false;
		}

	}

	@Override
	public void execute() {
		//intentionally left empty, unable to reach GL calls from this method

	}

	@Override
	public void update(NotificationType updateType) {
		switch(updateType){
		//if the model has updated, refresh the joints
		case modelTick:
			synchronized(lock){
				hasChanged = true;
			}
			break;
		}

	}

	@Override
	public void update(GL3 gl) {
		refreshJoints(gl);
	}

}
