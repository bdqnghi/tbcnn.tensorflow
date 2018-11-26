//
// Translated by CS2J (http://www.cs2j.com): 1/30/2014 10:47:53 AM
//

package DIaLOGIKa.b2xtranslator.StructuredStorage.Writer;

import CS2JNet.System.Collections.LCC.CSList;
import CS2JNet.System.StringSupport;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Common.DirectoryEntryColor;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Common.DirectoryEntryType;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Common.SectorId;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Writer.BaseDirectoryEntry;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Writer.StorageDirectoryEntry;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Writer.StreamDirectoryEntry;
import DIaLOGIKa.b2xtranslator.StructuredStorage.Writer.StructuredStorageContext;
import java.io.InputStream;
import java.util.UUID;

/*
 * Copyright (c) 2008, DIaLOGIKa
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of DIaLOGIKa nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY DIaLOGIKa ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL DIaLOGIKa BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
* Represents a storage directory entry in a structured storage.
* Author: math
*/
public class StorageDirectoryEntry  extends BaseDirectoryEntry 
{
    // The stream directory entries of this storage directory entry
    CSList<StreamDirectoryEntry> _streamDirectoryEntries = new CSList<StreamDirectoryEntry>();
    public CSList<StreamDirectoryEntry> getStreamDirectoryEntries() throws Exception {
        return _streamDirectoryEntries;
    }

    // The storage directory entries of this storage directory entry
    CSList<StorageDirectoryEntry> _storageDirectoryEntries = new CSList<StorageDirectoryEntry>();
    public CSList<StorageDirectoryEntry> getStorageDirectoryEntries() throws Exception {
        return _storageDirectoryEntries;
    }

    // The stream and storage directory entries of this storage directory entry
    CSList<BaseDirectoryEntry> _allDirectoryEntries = new CSList<BaseDirectoryEntry>();
    /**
    * Constructor.
    * 
    *  @param name The name of the directory entry.
    *  @param context The current context.
    */
    public StorageDirectoryEntry(String name, StructuredStorageContext context) throws Exception {
        super(name, context);
        setType(DirectoryEntryType.STGTY_STORAGE);
    }

    /**
    * Adds a stream directory entry to this storage directory entry.
    * 
    *  @param name The name of the stream directory entry to add.
    *  @param stream The stream referenced by the stream directory entry
    */
    public void addStreamDirectoryEntry(String name, InputStream stream) throws Exception {
        if (_streamDirectoryEntries.Exists())
        {
            return ;
        }
         
        StreamDirectoryEntry newDirEntry = new StreamDirectoryEntry(name,stream,getContext());
        _streamDirectoryEntries.add(newDirEntry);
        _allDirectoryEntries.add(newDirEntry);
    }

    /**
    * Adds a storage directory entry to this storage directory entry.
    * 
    *  @param name The name of the storage directory entry to add.
    *  @return The storage directory entry whic hahs been added.
    */
    public StorageDirectoryEntry addStorageDirectoryEntry(String name) throws Exception {
        StorageDirectoryEntry result = null;
        result = _storageDirectoryEntries.Find();
        if (result != null)
        {
            return result;
        }
         
        // entry exists
        result = new StorageDirectoryEntry(name,getContext());
        _storageDirectoryEntries.add(result);
        _allDirectoryEntries.add(result);
        return result;
    }

    /**
    * Sets the clsID.
    * 
    *  @param clsId The clsId to set.
    */
    public void setClsId(UUID clsId) throws Exception {
        setClsId(clsId);
    }

    /**
    * Recursively gets all storage directory entries starting at this directory entry.
    * 
    *  @return A list of directory entries.
    */
    public CSList<BaseDirectoryEntry> recursiveGetAllDirectoryEntries() throws Exception {
        CSList<BaseDirectoryEntry> result = new CSList<BaseDirectoryEntry>();
        return recursiveGetAllDirectoryEntries(result);
    }

    /**
    * The recursive implementation of the method RecursiveGetAllDirectoryEntries().
    */
    private CSList<BaseDirectoryEntry> recursiveGetAllDirectoryEntries(CSList<BaseDirectoryEntry> result) throws Exception {
        for (StorageDirectoryEntry entry : _storageDirectoryEntries)
        {
            result.AddRange(entry.recursiveGetAllDirectoryEntries());
        }
        for (StreamDirectoryEntry entry : _streamDirectoryEntries)
        {
            result.add(entry);
        }
        if (!result.contains(this))
        {
            result.add(this);
        }
         
        return result;
    }

    /**
    * Creates the red-black-tree recursively
    */
    public void recursiveCreateRedBlackTrees() throws Exception {
        this.setChildSiblingSid(createRedBlackTree());
        for (StorageDirectoryEntry entry : _storageDirectoryEntries)
        {
            entry.recursiveCreateRedBlackTrees();
        }
    }

    //foreach (BaseDirectoryEntry entry in _allDirectoryEntries)
    //{
    //    UInt32 left = entry.LeftSiblingSid;
    //    UInt32 right = entry.RightSiblingSid;
    //    UInt32 child = entry.ChildSiblingSid;
    //    Console.WriteLine("{0:X02}: Left: {2:X02}, Right: {3:X02}, Child: {4:X02}, Name: {1}, Color: {5}", entry.Sid, entry.Name, (left > 0xFF) ? 0xFF : left, (right > 0xFF) ? 0xFF : right, (child > 0xFF) ? 0xFF : child, entry.Color.ToString());
    //}
    //Console.WriteLine("----------");
    /**
    * Creates the red-black-tree for this directory entry
    */
    private long createRedBlackTree() throws Exception {
        _allDirectoryEntries.Sort(DirectoryEntryComparison);
        for (BaseDirectoryEntry entry : _allDirectoryEntries)
        {
            entry.setSid(getContext().getNewSid());
        }
        return setRelationsAndColorRecursive(this._allDirectoryEntries,(int)Math.Floor(Math.Log(_allDirectoryEntries.size(), 2)),0);
    }

    /**
    * Helper function for the method CreateRedBlackTree()
    * 
    *  @param entryList The list of directory entries
    *  @param treeHeight The height of the balanced red-black-tree
    *  @param treeLevel The current tree level
    *  @return The root of this red-black-tree
    */
    private long setRelationsAndColorRecursive(CSList<BaseDirectoryEntry> entryList, int treeHeight, int treeLevel) throws Exception {
        if (entryList.size() < 1)
        {
            return SectorId.FREESECT;
        }
         
        if (entryList.size() == 1)
        {
            if (treeLevel == treeHeight)
            {
                entryList.get(0).setColor(DirectoryEntryColor.DE_RED);
            }
             
            return entryList.get(0).getSid();
        }
         
        int middleIndex = getMiddleIndex(entryList);
        CSList<BaseDirectoryEntry> leftSubTree = entryList.GetRange(0, middleIndex);
        CSList<BaseDirectoryEntry> rightSubTree = entryList.GetRange(middleIndex + 1, entryList.size() - middleIndex - 1);
        int leftmiddleIndex = getMiddleIndex(leftSubTree);
        int rightmiddleIndex = getMiddleIndex(rightSubTree);
        if (leftSubTree.size() > 0)
        {
            entryList.get(middleIndex).setLeftSiblingSid(leftSubTree.get(leftmiddleIndex).getSid());
            setRelationsAndColorRecursive(leftSubTree,treeHeight,treeLevel + 1);
        }
         
        if (rightSubTree.size() > 0)
        {
            entryList.get(middleIndex).setRightSiblingSid(rightSubTree.get(rightmiddleIndex).getSid());
            setRelationsAndColorRecursive(rightSubTree,treeHeight,treeLevel + 1);
        }
         
        return entryList.get(middleIndex).getSid();
    }

    /**
    * Calculation of the middle index of a list of directory entries.
    * 
    *  @param list The input list.
    *  @return The result
    */
    private static int getMiddleIndex(CSList<BaseDirectoryEntry> list) throws Exception {
        return (int)Math.floor((list.size() - 1) / 2.0);
    }

    /**
    * Method for comparing directory entries (used in the red-black-tree).
    * 
    *  @param a The 1st directory entry.
    *  @param b The 2nd directory entry.
    *  @return Comparison result.
    */
    protected int directoryEntryComparison(BaseDirectoryEntry a, BaseDirectoryEntry b) throws Exception {
        if (a.getName().length() != b.getName().length())
        {
            return b.getName().length() == a.getName().length() ? 0 : (b.getName().length() > a.getName().length() ? 1 : -1);
        }
         
        String aU = a.getName().toUpperCase();
        String bU = b.getName().toUpperCase();
        for (int i = 0;i < aU.length();i++)
        {
            if ((long)aU.charAt(i) != (long)bU.charAt(i))
            {
                return (long)bU.charAt(i) == ((long)aU.charAt(i)) ? 0 : ((long)bU.charAt(i) > ((long)aU.charAt(i)) ? 1 : -1);
            }
             
        }
        return 0;
    }

}


