package impplugin.objects;

import java.io.Serializable;

public class Bodies implements Serializable{


	private String name;
	
	public Bodies(String name){
		this.name = name;
	}
	
	public String getName(){
		return name;
	}
	
	public void setName(String name){
		this.name = name;
	}
	
	
}
