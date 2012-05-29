package impplugin.objects;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import imp.core.commands.DynamicJointBuilder;
import imp.core.commands.JointArgumentInfo;
import imp.core.commands.JointBuilder;
import imp.core.exceptions.NonExistentJointEntry;

import imp.core.structures.Point;
import impplugin.PluginJointsLoader;

public class Joints implements Serializable{

	public static final String[] JOINT_TYPES = PluginJointsLoader.getTypes();
	
	private String name;
	private Bodies body1;
	private Bodies body2;
	private String type;
	private Point[] dataPoints;
	private Point origin;
	
	public Joints(String name, Bodies body1, Bodies body2, String jointType, Point[] dataPoints, Point origin){
		this.name = name;
		this.body1 = body1;
		this.body2 = body2;
		this.type = jointType;
		this.dataPoints = dataPoints;
		this.origin = origin;
	}
	
	public Point[] getDataPoints(){
		return dataPoints;
	}
	
	public String getName(){
		return name;
	}
	
	public Bodies getBody1(){
		return body1;
	}
	
	public Bodies getBody2(){
		return body2;
	}
	
	public String getType()
	{
		return type;
	}
	
	public Point getOrigin()
	{
		return origin;
	}
	
	public void setDataPoints(Point[] dataPoints){
		this.dataPoints = dataPoints;
	}
	
	public void setName(String name){
		this.name = name;
	}
	
	public void setBody1(Bodies body1){
		this.body1 = body1;
	}
	
	public void setBody2(Bodies body2){
		this.body2 = body2;
	}
	
	/*
	 * (non-Javadoc)
	 * Translates this class into a string format of IMP Code
	 * @see java.lang.Object#toString()
	 */
	public String toString()
	{
		String data = "";
		for(int i = 0; i < this.dataPoints.length; i++)
		{
			data += dataPoints[i].toString().replace(" ", "") + " ";
		}
		return this.type + " " + this.name + " " + this.body1.getName() + " " + this.body2.getName() + " " + origin.toString() + " " + data;
	}
}
