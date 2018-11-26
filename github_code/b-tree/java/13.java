/*
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 *
 */
package org.apache.directory.mavibot.btree;


/**
 * An enum to describe the B-tree type. We have three possible type :
 * <ul>
 * <li>IN_MEMORY : the B-tree will remain in memory, and won't be persisted on disk</li>
 * <li>BACKED_ON_DISK : the B-tree is in memory, but will be persisted on disk</li>
 * <li>PERSISTED : the B-tree is managed by a RecordManager, and some pages may
 * be swapped out from memory on demand</li>
 * <li>PERSISTED_SUB : The B-tree is a Persisted B-tree, but a Sub B-tree one</li>
 * <li>PERSISTED_MANAGEMENT : This is a Persisted B-tree used to manage the other B-trees</li>
 * </ul>
 *
 * @author <a href="mailto:dev@directory.apache.org">Apache Directory Project</a>
 */
public enum BTreeTypeEnum
{
    /** Pure in-memory B-tree, not persisted on disk */
    IN_MEMORY,

    /** Persisted B-tree */
    PERSISTED,

    /** Persisted sub B-tree */
    PERSISTED_SUB,

    /** Persisted Management B-tree */
    BTREE_OF_BTREES,

    /** Persisted Management B-tree */
    COPIED_PAGES_BTREE,

    /** In-memory B-tree but saved on disk */
    BACKED_ON_DISK
}
