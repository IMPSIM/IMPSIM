/**
 * Name.java
 * Sep 18, 2011
 */
package imp.core.expressions.attributes;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;



/**
 * Annotation for imp functions
 * 
 * @author zastrowm
 * @version 1.0
 */

@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Function {
	
	public String value();
	
}
