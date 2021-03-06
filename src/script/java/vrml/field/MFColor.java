//
// OpenVRML
//
// Copyright 2001  Henri Manson
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
 * Represents a VRML MFColor field in Java.
 */
public class MFColor extends MField {

    /**
     * Construct a new MFColor field in OpenVRML using the given params.
     *
     * @param size Number of SFColor elements passed in.
     * @param colors List of RGB 3-tuples
     */
    static native long createPeer(int size, float colors[]);

    /**
     * Construct a new MFColor field in OpenVRML using the given params.
     *
     * @param colors An array of sets of three-float values (RGB)
     */
    static native long createPeer(float colors[][]);

    /**
     * Default constructor.
     */
    public MFColor() {
        this(0, null);
    }

    /**
     * Construct from a peer handle.
     */
    MFColor(long peer) {
        super(peer);
    }

    /**
     * Construct a new MFColor object using the given 2D array containing
     * RGB values.
     *
     * @param colors An array of sets of three float values (RGB)
     */
    public MFColor(float colors[][]) {
        super(createPeer(colors));
    }

    /**
     * Construct an MFColor field.
     *
     * @param colors An array of RGB value
     */
    public MFColor(float colors[]) {
        super(createPeer(colors.length / 3, colors));
    }

    /**
     * Construct an MFColor field.
     *
     * @param size Number of SFColor elements passed in.
     * @param colors List of RGB 3-tuples
     */
    public MFColor(int size, float colors[]) {
        super(createPeer(size, colors));
    }

    public native int getSize();

    public native void clear();

    public native void delete(int index);

    /**
     * Retrieves the value of an MFColor field.
     *
     * @param colors 2D array of sets of RGB values to be returned.
     */
    public native void getValue(float colors[][]);

    /**
     * Retrieves the value of an MFColor field.
     *
     * @param colors Array of sets of RGB values to be returned.
     */
    public native void getValue(float colors[]);

    /**
     * Retrieves a specific SFColor element in an MFColor and
     * returns it as a float array.
     *
     * @param index Position of desired SFColor
     * @param colors RGB value of specified SFColor.
     */
    public native void get1Value(int index, float colors[]);

    /**
     * Retrieves a specific SFColor element in an MFColor and
     * returns it as an SFColor object.
     *
     * @param index Position of desired SFColor
     * @param color SFColor that will be set to desired value.
     */
    public void get1Value(int index, SFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        this.get1Value(index, c);
        color.setValue(c);
    }

    /**
     * Set the value of an MFColor field.
     *
     * @param colors Array of array of RGB values.
     */
    public native void setValue(float colors[][]);

    /**
     * Set the value of an MFColor field.
     *
     * @param colors Array of RGB values.
     */
    public void setValue(float colors[]) {
        this.setValue(colors.length / 3, colors);
    }

    /**
     * Set the value of an MFColor field.
     *
     * @param size Number of elements to put in MFColor field.
     * @param colors Array of RGB values.
     */
    public native void setValue(int size, float colors[]);

    /**
     * Set the value of an MFColor field.
     *
     * @param colors Existing MFColor object to copy values from.
     */
    public native void setValue(MFColor colors);

    /**
     * Set the value of an MFColor field.
     *
     * @param colors Existing ConstMFColor object to copy values from.
     */
    public native void setValue(ConstMFColor colors);

    /**
     * Set an element in an MFColor field.
     *
     * @param index Position of element to set.
     * @param color Value to set element to.
     */
    public void set1Value(int index, ConstSFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.set1Value(index, c[0], c[1], c[2]);
    }

    /**
     * Set an element in an MFColor field.
     *
     * @param index Position of element to set.
     * @param color Value to set element to.
     */
    public void set1Value(int index, SFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.set1Value(index, c[0], c[1], c[2]);
    }

    /**
     * Set an element in an MFColor field.
     *
     * @param index Position of element to set.
     * @param red R-component of new color.
     * @param green G-component of new color.
     * @param blue B-component of new color.
     */
    public native void set1Value(int index, float red, float green,
                                 float blue);

    /**
     * Append a new element to the end of an MFColor field.
     *
     * @param color Value to append.
     */
    public void addValue(ConstSFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.addValue(c[0], c[1], c[2]);
    }

    /**
     * Append a new element to the end of an MFColor field.
     *
     * @param color Value to append.
     */
    public void addValue(SFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.addValue(c[0], c[1], c[2]);
    }

    /**
     * Append a new element to the end of an MFColor field.
     *
     * @param red R-component of new element.
     * @param green G-component of new element.
     * @param blue B-component of new element.
     */
    public native void addValue(float red, float green, float blue);

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param color Value to insert.
     */
    public void insertValue(int index, ConstSFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.insertValue(index, c[0], c[1], c[2]);
    }

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param color Value to insert.
     */
    public void insertValue(int index, SFColor color) {
        float[] c = { 0.0f, 0.0f, 0.0f };
        color.getValue(c);
        this.insertValue(index, c[0], c[1], c[2]);
    }

    /**
     * Insert a new element at the specified position.
     *
     * @param index Position to insert new element at.
     * @param red R-component of new element.
     * @param green G-component of new element.
     * @param blue B-component of new element.
     */
    public native void insertValue(int index, float red, float green,
                                   float blue);
}
