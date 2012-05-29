package impplugin.objects;

import java.util.ArrayList;

public class Storage {

	private ArrayList<Joints> joints;
	private ArrayList<Bodies> bodies;
	
	
	public Storage(){
		
		bodies = new ArrayList<>();
		joints = new ArrayList<>();
	}
	
	
	
	public void addBody(Bodies body){
		bodies.add(body);
	}
	
	public void addJoint(Joints joint){
		joints.add(joint);
	}
	
	
	public ArrayList<Bodies> getBodies(){
		return bodies;
	}
	
	
	public ArrayList<Joints> getJoints(){
		return joints;
	}
	
	
	public Bodies getBody(String name){
		Bodies retval = null;
		for(int i=0; i<bodies.size(); i++){
			if(bodies.get(i).getName().equals(name)){
				retval = bodies.get(i);
			}
		}
		return retval;
	}
	
	
	public Joints getJoint(String name){
		Joints retval = null;
		for(int i=0; i<joints.size(); i++){
			if(joints.get(i).getName().equals(name)){
				retval = joints.get(i);
			}
		}
		return retval;
	}
	
	public void removeJoint(String name){
		for(int i=0; i<joints.size(); i++){
			if(joints.get(i).getName().equals(name)){
				joints.remove(i);
			}
		}
	}
	
	public void removeBody(String name){
		for(int i=0; i<bodies.size(); i++){
			if(bodies.get(i).getName().equals(name)){
				bodies.remove(i);
			}
		}
	}
	
}
