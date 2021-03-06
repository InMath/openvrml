//
// OpenVRML
//
// Copyright 2008  Braden McDaniel
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

package vrml.field;

import vrml.MField;

/**
 * Represents a VRML MFVec3d field in Java.
 */
public class MFVec3d extends MField {

    /**
     * Construct a new MFVec3d field in OpenVRML using the given params.
     *
     * @param vec3s An array of sets of x,y,z values
     */
    static native long createPeer(double vec3s[][]);

    /**
     * Construct a new MFVec3d field in OpenVRML using the given params.
     *
     * @param size Number of SFVec3d elements passed in.
     * @param vec3s List of x,y,z tuples
     */
    static native long createPeer(int size, double vec3s[]);

    /**
     * Default constructor.
     */
    public MFVec3d() {
        this(0, null);
    }

    /**
     * Construct from a peer handle.
     */
    MFVec3d(long peer) {
        super(peer);
    }

    /**
     * Construct an MFVec3d field.
     *
     * @param vec3s An array of sets of x,y,z values
     */
    public MFVec3d(double vec3s[][]) {
        super(createPeer(vec3s));
    }

    /**
     * Construct an MFVec3d field.
     *
     * @param vec3s List of x,y,z tuples
     */
    public MFVec3d(double vec3s[]) {
        this(vec3s.length / 3, vec3s);
    }

    /**
     * Construct an MFVec3d field.
     *
     * @param size Number of SFVec3d elements passed in.
     * @param vec3s List of x,y,z tuples
     */
    public MFVec3d(int size, double vec3s[]) {
        super(createPeer(size, vec3s));
    }

    public native int getSize();

    public native void clear();

    public native void delete(int index);

    /**
     * Retrieves the value of an MFVec3d field.
     *
     * @param vec3s 2D array of x,y,z tuples to be returned.
     */
    public native void getValue(double vec3s[][]);

    /**
     * Retrieves the value of an MFVec3d field.
     *
     * @param vec3s Array of x,y,z tuples to be returned.
     */
    public native void getValue(double vec3s[]);

    /**
     * Retrieves a specific element in an MFVec3d and
     * returns it as a double array.
     *
     * @param index Position of desired element
     * @param vec3s Element at specified position
     */
    public native void get1Value(int index, double vec3s[]);

    /**
     * Retrieves a specific element in an MFVec3d and
     * returns it as an SFVec3d.
     *
     * @param index Position of desired element
     * @param vec Element at specified position
     */
    public void get1Value(int index, SFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        this.get1Value(index, v);
        vec.setValue(v);
    }

    /**
     * Set the value of the field.
     *
     * @param vec3s New value for field.
     */
    public native void setValue(double vec3s[][]);

    /**
     * Set the value of the field.
     *
     * @param vec3s New value for field.
     */
    public void setValue(double vec3s[]) {
        this.setValue(vec3s.length / 3, vec3s);
    }

    /**
     * Set the value of the field.
     *
     * @param size Size of new value for field.
     * @param vec3s New value for field.
     */
    public native void setValue(int size, double vec3s[]);

    /**
     * Set the value of the field.
     *
     * @param vecs New value for field.
     */
    public native void setValue(MFVec3d vecs);

    /**
     * Set the value of the field.
     *
     * @param vecs New value for field.
     */
    public native void setValue(ConstMFVec3d vecs);

    /**
     * Set a specified element in the field.
     *
     * @param index Position of element to update.
     * @param x X-component of new value.
     * @param y Y-component of new value.
     * @param z Z-component of new value.
     */
    public native void set1Value(int index, double x, double y, double z);

    /**
     * Set a specified element in the field.
     *
     * @param index Position of element to update.
     * @param vec New value for element.
     */
    public void set1Value(int index, ConstSFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.set1Value(index, v[0], v[1], v[2]);
    }

    /**
     * Set a specified element in the field.
     *
     * @param index Position of element to update.
     * @param vec New value for element.
     */
    public void set1Value(int index, SFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.set1Value(index, v[0], v[1], v[2]);
    }

    /**
     * Add a new element at the end of the list.
     *
     * @param x X-component of the vector to add.
     * @param y Y-component of the vector to add.
     * @param z Z-component of the vector to add.
     */
    public native void addValue(double x, double y, double z);

    /**
     * Add a new element at the end of the list.
     *
     * @param vec Element to add.
     */
    public void addValue(ConstSFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.addValue(v[0], v[1], v[2]);
    }

    /**
     * Add a new element at the end of the list.
     *
     * @param vec Element to add.
     */
    public void addValue(SFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.addValue(v[0], v[1], v[2]);
    }

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param x X-component of value to insert.
     * @param y Y-component of value to insert.
     * @param z Z-component of value to insert.
     */
    public native void insertValue(int index, double x, double y, double z);

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param vec Value to insert.
     */
    public void insertValue(int index, ConstSFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.insertValue(index, v[0], v[1], v[2]);
    }

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param vec Value to insert.
     */
    public void insertValue(int index, SFVec3d vec) {
        double[] v = { 0.0, 0.0, 0.0 };
        vec.getValue(v);
        this.insertValue(index, v[0], v[1], v[2]);
    }
}
