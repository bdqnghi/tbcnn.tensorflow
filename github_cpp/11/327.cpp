#include "QuadTree.h"
#include "BuildingTextureInfo.h"

QuadTree::QuadTree(Rectangle3D bound)
{
    count = 0;
    bounds = bound;
    topLeft = topRight = bottomLeft = bottomRight = NULL;
}

bool QuadTree::Add(Building *building)
{
    // CHeck if it can go here
    if (!bounds.Intersects(building->bounds))
        return false;

    // Try and fit it in here
    if (count < QUAD_TREE_CAPACITY)
    {
        buildings[count++] = building;
        return true;
    }

    // Else we have to split
    if (topLeft == NULL)
    {
        float hW = bounds.width / 2.0f;
        float hH = bounds.depth / 2.0f;
        float x = bounds.topLeft.x;
        float y = bounds.topLeft.y;

        topLeft = new QuadTree(Rectangle3D(x, y, hW, hH, bounds.height));
        topRight = new QuadTree(Rectangle3D(x + hW, y, hW, hH, bounds.height));
        bottomLeft = new QuadTree(Rectangle3D(x, y + hH, hW, hH, bounds.height));
        bottomRight = new QuadTree(Rectangle3D(x + hW, y + hH, hW, hH, bounds.height));
    }

    // Give it to the children
    if (topLeft->Add(building))
        return true;
    if (topRight->Add(building))
        return true;
    if (bottomLeft->Add(building))
        return true;
    if (bottomRight->Add(building))
        return true;

    // Shouldn't really happen :P
    printf("ERROR: QUAD TREE IS BROKEN\n");
    return false;
}

void QuadTree::GetBuildings(Frustum *frustum, std::vector<Building*> &buildings1, std::vector<Building*> &buildings2)
{
    // Do a depth traversal
    std::stack<QuadTree*> stack;
    stack.push(this);

    while (!stack.size() == 0)
    {        
        QuadTree *node = stack.top();
        stack.pop();

        if (!frustum->InFrustum(node->bounds))
            continue;

        for (int i = 0; i < node->count; i++)
        {
            Building* building = node->buildings[i];
            if (frustum->InFrustum(building->bounds))
            {
                if (building->textureIndex == 0)
                {
                    buildings1.push_back(building);
                }
                else
                {
                    buildings2.push_back(building);
                }
            }
        }

        if (node->topLeft != NULL)
        {
            stack.push(node->topLeft);
            stack.push(node->topRight);
            stack.push(node->bottomLeft);
            stack.push(node->bottomRight);
        }
    }    
}

void QuadTree::DrawAll(Frustum *frustum)
{
    // Store the bulidings based on texture
    std::vector<Building*> v1, v2;

    GetBuildings(frustum, v1, v2);    
    
    // Set up textures
    int textureIndex = -1;

    if (v1.size() > 0)
    {
        textureIndex = 0;
    }

    if (v2.size() > 0 && textureIndex == -1)
    {
        textureIndex = 1;
    }

    // No buildings
    if (textureIndex == -1)
        return;

    // Bind side windows
    glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingTextures[textureIndex]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingNormalMaps[textureIndex]);

    // Bind front windows
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingTextures[BuildingTextureInfo::buildingTextureRoofIndex]);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingNormalMaps[BuildingTextureInfo::buildingTextureRoofIndex]);

    for (int i = 0; i < 5; i++)
    {
        glEnableVertexAttribArray(i);
    }

    for (std::vector<Building*>::iterator it = v1.begin(); it < v1.end(); it++)
    {
        Building* building = *it;
        glBindBuffer(GL_ARRAY_BUFFER, building->m_vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, building->m_indexBuffer);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(BuildingVertex), NULL);        
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (3 * sizeof(float)));        
        glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (6 * sizeof(float)));        
        glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (9 * sizeof(float)));        
        glVertexAttribPointer(4, 2, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (12 * sizeof(float)));

        glDrawElements(GL_TRIANGLES, building->indCount, GL_UNSIGNED_INT, 0);
    }

    if (textureIndex != 1 && v2.size() > 0)
    {
        textureIndex = 1;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingTextures[textureIndex]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, BuildingTextureInfo::buildingNormalMaps[textureIndex]);
    }

    for (std::vector<Building*>::iterator it = v2.begin(); it < v2.end(); it++)
    {
        Building* building = *it;
        glBindBuffer(GL_ARRAY_BUFFER, building->m_vertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, building->m_indexBuffer);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(BuildingVertex), NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (3 * sizeof(float)));
        glVertexAttribPointer(2, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (6 * sizeof(float)));
        glVertexAttribPointer(3, 3, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (9 * sizeof(float)));
        glVertexAttribPointer(4, 2, GL_FLOAT, false, sizeof(BuildingVertex), (unsigned char*)NULL + (12 * sizeof(float)));

        glDrawElements(GL_TRIANGLES, building->indCount, GL_UNSIGNED_INT, 0);
    }


    for (int i = 0; i < 5; i++)
    {
        glDisableVertexAttribArray(i);
    }

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

}