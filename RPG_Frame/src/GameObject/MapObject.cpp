#include	"MapObject.h"
#include	"MapSpriteComponent.h"
#include	"Game.h"
#include    <Python.h>
#include    <stdlib.h>
#include    <algorithm>
#include    "Math2.h"


GameFrame::MapObject::MapObject(Game* game, const char* fileName, const std::string& name) :
    tilewidth(0),
    tileheight(0),
    GameObject(game, name)
{
    LoadMapXml(fileName);
    PhysWorld* phys = new PhysWorld();
    Pw = phys;
}

GameFrame::MapObject::~MapObject()
{
}

void GameFrame::MapObject::update()
{
}

void GameFrame::MapObject::Draw(SDL_Renderer* renderer)
{
    for (auto iter = mLayers.begin(); iter != mLayers.end(); iter++) {
        DrawLayer(renderer,*iter);
    }
    for (auto iter : mMapObjects) {
        iter->Draw(renderer);
    }
}

void GameFrame::MapObject::DrawLayer(SDL_Renderer* renderer, Layer* layer)
{
    SDL_Texture* tex = GetGame()->GetTexture(layer->tilePath);
    int textureW = tilewidth;
    int textureH = tileheight;

    int it = 0;
    SDL_Rect imageRect{ 0,0,textureW,textureH };
    SDL_Rect dstRect{ 0, 0, TILEW, TILEH };

    for (auto iter : layer->Lcode) {
        if (iter == -1) {
            it++;
            continue;
        }
            
        //���ͼƬid��ת��Ϊ��ͼ��ȡ����
        Vector2 idvec = layer->TileIdParser(iter,tex);
        imageRect.x = idvec.x * textureW;
        imageRect.y = idvec.y * textureH;

        //������idת��Ϊ����Ŀ������
        Vector2 itvec = layer->MapIdParser(it);
        dstRect.x = itvec.x * TILEW;
        dstRect.y = itvec.y * TILEH;

        //����
        SDL_RenderCopy(renderer, tex, &imageRect, &dstRect);
        it++;
    };
        
}

void GameFrame::MapObject::AddMapObject(GameObject* gameobject)
{
    mMapObjects.emplace_back(gameobject);
}

void GameFrame::MapObject::RemoveMapObject(GameObject* gameobject)
{
    auto iter = std::find(mMapObjects.begin(), mMapObjects.end(), gameobject);
    if (iter != mMapObjects.end()) {
        std::iter_swap(iter, mMapObjects.end() - 1);
        mMapObjects.pop_back();
    }
}

void GameFrame::MapObject::LoadMapXml(const char* filepath)
{
    //��ȡtmx��ʽ��ͼ�ļ�
    TiXmlDocument doc(filepath);
    if (!doc.LoadFile()) {
        printf("Could not load test file %s. Error='%s'. Exiting.\n", filepath, doc.ErrorDesc());
        exit(1);
    }

    TiXmlElement* root = doc.RootElement();
    if (!root) {
        exit(1);
    }

    //�����ͼ����
    auto name = root->Attribute("name");
    if (name) {
        MapName = name;
    }
    auto width = root->Attribute("width");
    if (width) {
        MapW = atoi(width);
    }
    auto height = root->Attribute("height");
    if (height) {
        MapH = atoi(height);
    }

    auto tw = root->Attribute("tilewidth");
    if (tw) {
        tilewidth = atoi(tw);
    }

    auto hw = root->Attribute("tileheight");
    if (hw) {
        tileheight = atoi(hw);
    }

    //������һ�ڵ��ǩtileset
    TiXmlElement* tileset = root->FirstChildElement("tileset");
    if (!tileset) {
        exit(1);
    }

    auto layer = tileset->NextSibling();
    int layercount = 0;
    while (layer) {
        layercount++;
        auto attr = layer->ToElement();
        Layer* L = new Layer;
        L->LayerName = attr->Attribute("name");
        L->width = atoi(attr->Attribute("width"));// *tilewidth;
        L->height = atoi(attr->Attribute("height"));// *tileheight;
        L->zlibcode = layer->FirstChild()->ToElement()->GetText();
        L->UpdateOrder = layercount;
        size_t output_length = 0;
        UncompressPy(L);
        mLayers.emplace_back(L);
        layer = layer->NextSibling();//��ȡ����һ���ֵܽڵ�
    }
}


void GameFrame::MapObject::UncompressPy(Layer* layer)
{
    const char* zlibcode = layer->zlibcode;
    PyObject*  pModule = PyImport_ImportModule("uncompress");
    //����
    PyObject* pArgs = PyTuple_New(1);//��������Ԫ�飬Ԫ���СΪ1������
    PyObject* pFunc = PyObject_GetAttrString(pModule, "UncompressFc");
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", zlibcode));//Py_BuildValue������ת��Ϊpy���ַ������ݽṹ

    //ʹ��C++��python�ӿڵ��øú���,����python����õķ���ֵ
    PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
    //��Ԫ�����еĲ���һ����ת����int��������
    for (int i = 0; i < layer->height * layer->width; i++) {
        PyObject* b = PyTuple_GetItem(pReturn, i);
        int c;
        PyArg_Parse(b, "i", &c);
        layer->Lcode.emplace_back(c-1);
    }
}

void GameFrame::PhysWorld::AddBox(CollisionComponent* box)
{
	mBox.emplace_back(box);
}

void GameFrame::PhysWorld::RemoveBox(CollisionComponent* box)
{
    auto iter = std::find(mBox.begin(), mBox.end(), box);
    if (iter != mBox.end()) {
        mBox.erase(iter);
    }
}

GameFrame::Vector2 GameFrame::Layer::TileIdParser(int id, SDL_Texture* tex)
{
    int textureW, textureH;Vector2 vec;
    SDL_QueryTexture(tex, nullptr, nullptr, &textureW, &textureH);
    textureW = textureW / 16;
    textureH = textureH / 16;
    vec.x = id % textureW;
    vec.y = id / textureW;
    return vec;
}

GameFrame::Vector2 GameFrame::Layer::MapIdParser(int it)
{
    Vector2 vec;
    vec.x = it % width;
    vec.y = it / width;
    return vec;
}
