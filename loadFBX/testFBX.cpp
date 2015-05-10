#include <fbxsdk.h>
#include <vector>
#include <glm/glm.hpp>

#include "src/DisplayMesh.h"


/* Tab character ("\t") counter */
int numTabs = 0; 

/**
 * Print the required number of tabs.
 */
void PrintTabs() {
    for(int i = 0; i < numTabs; i++)
        printf("\t");
}

/**
 * Return a string-based representation based on the attribute type.
 */
FbxString GetAttributeTypeName(FbxNodeAttribute::EType type) { 
    switch(type) { 
        case FbxNodeAttribute::eUnknown: return "unidentified"; 
        case FbxNodeAttribute::eNull: return "null"; 
        case FbxNodeAttribute::eMarker: return "marker"; 
        case FbxNodeAttribute::eSkeleton: return "skeleton"; 
        case FbxNodeAttribute::eMesh: return "mesh"; 
        case FbxNodeAttribute::eNurbs: return "nurbs"; 
        case FbxNodeAttribute::ePatch: return "patch"; 
        case FbxNodeAttribute::eCamera: return "camera"; 
        case FbxNodeAttribute::eCameraStereo: return "stereo"; 
        case FbxNodeAttribute::eCameraSwitcher: return "camera switcher"; 
        case FbxNodeAttribute::eLight: return "light"; 
        case FbxNodeAttribute::eOpticalReference: return "optical reference"; 
        case FbxNodeAttribute::eOpticalMarker: return "marker"; 
        case FbxNodeAttribute::eNurbsCurve: return "nurbs curve"; 
        case FbxNodeAttribute::eTrimNurbsSurface: return "trim nurbs surface"; 
        case FbxNodeAttribute::eBoundary: return "boundary"; 
        case FbxNodeAttribute::eNurbsSurface: return "nurbs surface"; 
        case FbxNodeAttribute::eShape: return "shape"; 
        case FbxNodeAttribute::eLODGroup: return "lodgroup"; 
        case FbxNodeAttribute::eSubDiv: return "subdiv"; 
        default: return "unknown"; 
    } 
}

/**
 * Print an attribute.
 */
void PrintAttribute(FbxNodeAttribute* pAttribute) {
    if(!pAttribute) return;
 
    FbxString typeName = GetAttributeTypeName(pAttribute->GetAttributeType());
    FbxString attrName = pAttribute->GetName();
    PrintTabs();
    // Note: to retrieve the character array of a FbxString, use its Buffer() method.
    printf("<attribute type='%s' name='%s'/>\n", typeName.Buffer(), attrName.Buffer());
}

/**
 * Print a node, its attributes, and all its children recursively.
 */
void PrintNode2(FbxNode* pNode) {
    PrintTabs();
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get(); 
    FbxDouble3 rotation = pNode->LclRotation.Get(); 
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // Print the contents of the node.
    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n", 
        nodeName, 
        translation[0], translation[1], translation[2],
        rotation[0], rotation[1], rotation[2],
        scaling[0], scaling[1], scaling[2]
        );
    numTabs++;

    // Print the node's attributes.
    for(int i = 0; i < pNode->GetNodeAttributeCount(); i++)
        PrintAttribute(pNode->GetNodeAttributeByIndex(i));

    // Recursively print the children.
    for(int j = 0; j < pNode->GetChildCount(); j++)
        PrintNode2(pNode->GetChild(j));

    numTabs--;
    PrintTabs();
    printf("</node>\n");
}

void PrintNode(FbxNode* pNode) {
    PrintTabs();
    const char* nodeName = pNode->GetName();
    FbxDouble3 translation = pNode->LclTranslation.Get();
    FbxDouble3 rotation = pNode->LclRotation.Get();
    FbxDouble3 scaling = pNode->LclScaling.Get();

    // Print the contents of the node.
    printf("<node name='%s' translation='(%f, %f, %f)' rotation='(%f, %f, %f)' scaling='(%f, %f, %f)'>\n",
           nodeName,
           translation[0], translation[1], translation[2],
           rotation[0], rotation[1], rotation[2],
           scaling[0], scaling[1], scaling[2]
    );
    numTabs++;

    // Print the node's attributes.
    for(int i = 0; i < pNode->GetNodeAttributeCount(); i++)
        PrintAttribute(pNode->GetNodeAttributeByIndex(i));

    numTabs--;
    PrintTabs();
    printf("</node>\n");
}

void proceedMesh(FbxNode* pNode,
                 std::vector<glm::vec3> &out_vertices,
                 std::vector<glm::vec2> &out_uvs,
                 std::vector<glm::vec3> &out_normals
) {

    FbxMesh* pMesh = (FbxMesh*) pNode->GetNodeAttribute ();

    std::vector<glm::vec3> cpToNormals;

    int lControlPointsCount = pMesh->GetControlPointsCount();
    FbxVector4* lControlPoints = pMesh->GetControlPoints();

    DisplayString("    Control Points");

    for (int i = 0; i < lControlPointsCount; i++)
    {
        DisplayInt("        Control Point ", i);
//        Display3DVector("            Coordinates: ", lControlPoints[i]);

        for (int j = 0; j < pMesh->GetElementNormalCount(); j++)
        {
            FbxGeometryElementNormal* leNormals = pMesh->GetElementNormal( j);
            if (leNormals->GetMappingMode() == FbxGeometryElement::eByControlPoint)
            {
//                char header[100];
//                FBXSDK_sprintf(header, 100, "            Normal Vector: ");
                if (leNormals->GetReferenceMode() == FbxGeometryElement::eDirect) {
                    FbxVector4 tmp = leNormals->GetDirectArray().GetAt(i);
//                    Display3DVector(header, tmp);
                    cpToNormals.push_back(glm::vec3(tmp[0], tmp[1], tmp[2]));
                }
            }
        }
    }

    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    int lPolygonCount = pMesh->GetPolygonCount();
//    FbxVector4* lControlPoints = pMesh->GetControlPoints();
    char header[100];

    DisplayString("    Polygons");

    int vertexId = 0;
    for (int i = 0; i < lPolygonCount; i++)
    {
        DisplayInt("        Polygon ", i);
        int l;

        int lPolygonSize = pMesh->GetPolygonSize(i);

        for (int j = 0; j < lPolygonSize; j++)
        {
            int lControlPointIndex = pMesh->GetPolygonVertex(i, j);

            FbxVector4 pValue = lControlPoints[lControlPointIndex];
            out_vertices.push_back(glm::vec3(pValue[0], pValue[1], pValue[2]));

//            Display3DVector("            Coordinates: ", pValue);

            for (l = 0; l < pMesh->GetElementUVCount(); ++l)
            {
                FbxGeometryElementUV* leUV = pMesh->GetElementUV( l);
                FBXSDK_sprintf(header, 100, "            Texture UV: ");

                switch (leUV->GetMappingMode())
                {
                    default:
                        break;
                    case FbxGeometryElement::eByControlPoint:
                        printf("FbxGeometryElement::eByControlPoint\n");
                        switch (leUV->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                                printf("FbxGeometryElement::eDirect\n");
                                Display2DVector(header, leUV->GetDirectArray().GetAt(lControlPointIndex));
                                break;
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                printf("FbxGeometryElement::eIndexToDirect\n");
                                int id = leUV->GetIndexArray().GetAt(lControlPointIndex);
                                Display2DVector(header, leUV->GetDirectArray().GetAt(id));
                            }
                                break;
                            default:
                                break; // other reference modes not shown here!
                        }
                        break;

                    case FbxGeometryElement::eByPolygonVertex:
                    {
//                        printf("FbxGeometryElement::eByPolygonVertex\n");
                        int lTextureUVIndex = pMesh->GetTextureUVIndex(i, j);
                        switch (leUV->GetReferenceMode())
                        {
                            case FbxGeometryElement::eDirect:
                            case FbxGeometryElement::eIndexToDirect:
                            {
                                FbxVector2 tmp0 = leUV->GetDirectArray().GetAt(lTextureUVIndex);
//                                Display2DVector(header, tmp0);
                                out_uvs.push_back(glm::vec2(tmp0[0], tmp0[1]));
                                out_normals.push_back(cpToNormals[i]);
                                break;
                            }
                            default:
                                break; // other reference modes not shown here!
                        }
                    }
                        break;

                    case FbxGeometryElement::eByPolygon: // doesn't make much sense for UVs
                    case FbxGeometryElement::eAllSame:   // doesn't make much sense for UVs
                    case FbxGeometryElement::eNone:       // doesn't make much sense for UVs
                        break;
                }
            }
            for( l = 0; l < pMesh->GetElementNormalCount(); ++l)
            {
                FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal( l);
                FBXSDK_sprintf(header, 100, "            Normal: ");

                if(leNormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leNormal->GetReferenceMode()) {
                        case FbxGeometryElement::eDirect: {
                            FbxVector4 tmp1 = leNormal->GetDirectArray().GetAt(vertexId);
                            Display3DVector(header, tmp1);
                            break;
                        }
                        case FbxGeometryElement::eIndexToDirect: {
                            int id = leNormal->GetIndexArray().GetAt(vertexId);
                            FbxVector4 tmp2 = leNormal->GetDirectArray().GetAt(id);
                            Display3DVector(header, tmp2);
                            break;
                        }
                        default:
                            break; // other reference modes not shown here!
                    }
                }

            }
            for( l = 0; l < pMesh->GetElementTangentCount(); ++l)
            {
                FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent( l);
                FBXSDK_sprintf(header, 100, "            Tangent: ");

                if(leTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leTangent->GetReferenceMode())
                    {
                        case FbxGeometryElement::eDirect:
                            Display3DVector(header, leTangent->GetDirectArray().GetAt(vertexId));
                            break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id = leTangent->GetIndexArray().GetAt(vertexId);
                            Display3DVector(header, leTangent->GetDirectArray().GetAt(id));
                        }
                            break;
                        default:
                            break; // other reference modes not shown here!
                    }
                }

            }
            for( l = 0; l < pMesh->GetElementBinormalCount(); ++l)
            {

                FbxGeometryElementBinormal* leBinormal = pMesh->GetElementBinormal( l);

                FBXSDK_sprintf(header, 100, "            Binormal: ");
                if(leBinormal->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
                {
                    switch (leBinormal->GetReferenceMode())
                    {
                        case FbxGeometryElement::eDirect:
                            Display3DVector(header, leBinormal->GetDirectArray().GetAt(vertexId));
                            break;
                        case FbxGeometryElement::eIndexToDirect:
                        {
                            int id = leBinormal->GetIndexArray().GetAt(vertexId);
                            Display3DVector(header, leBinormal->GetDirectArray().GetAt(id));
                        }
                            break;
                        default:
                            break; // other reference modes not shown here!
                    }
                }
            }
            vertexId++;
        } // for polygonSize
    } // for polygonCount


    // 1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




}


void loadMesh(FbxNode* pNode) {

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals; // Won't be used at the moment.

    proceedMesh(pNode, vertices, uvs, normals);

    assert(vertices.size() == uvs.size());
    assert(vertices.size() == normals.size());

    printf("sizes: %lu, %lu, %lu;\n", vertices.size(), uvs.size(), normals.size());



}



/**
 * Main function - loads the hard-coded fbx file,
 * and prints its contents in an xml format to stdout.
 */
int main(int argc, char** argv) {

    // Change the following filename to a suitable filename value.
    const char* lFilename = "/Users/oleg/data/Granate.fbx";
//    const char* lFilename = "/Users/oleg/data/cube.obj";

    // Initialize the SDK manager. This object handles all our memory management.
    FbxManager* lSdkManager = FbxManager::Create();
    
    // Create the IO settings object.
    FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create an importer using the SDK manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");
    
    // Use the first argument as the filename for the importer.
    if(!lImporter->Initialize(lFilename, -1, lSdkManager->GetIOSettings())) { 
        printf("Call to FbxImporter::Initialize() failed.\n"); 
        printf("Error returned: %s\n\n", lImporter->GetStatus().GetErrorString()); 
        exit(-1); 
    }
    
    // Create a new scene so that it can be populated by the imported file.
    FbxScene* lScene = FbxScene::Create(lSdkManager,"myScene");

    // Import the contents of the file into the scene.
    lImporter->Import(lScene);

    // The file is imported; so get rid of the importer.
    lImporter->Destroy();

    printf("OLOLO\n");

    // Print the nodes 2of the scene and their attributes recursively.
    // Note that we are not printing the root node because it should
    // not contain any attributes.
    FbxNode* lRootNode = lScene->GetRootNode();
    if(lRootNode) {
        for(int i = 0; i < lRootNode->GetChildCount(); i++) {
            FbxNode *currentNode = lRootNode->GetChild(i);
            FbxNodeAttribute::EType lAttributeType;
            lAttributeType = (currentNode->GetNodeAttribute()->GetAttributeType());
            if (lAttributeType == FbxNodeAttribute::eMesh) {
                loadMesh(currentNode);
            }
        }
    }
    // Destroy the SDK manager and all the other objects it was handling.
    lSdkManager->Destroy();
    return 0;
}
