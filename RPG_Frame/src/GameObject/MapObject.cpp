#include	"MapObject.h"
#include	"Game.h"
#include    <Python.h>
#include    <stdlib.h>
#include    <algorithm>
#include    "Math2.h"
using json = nlohmann::json;

GameFrame::MapObject::MapObject(Game* game, const std::string& fileName, const std::string& name) :
    tileW(TILEW),
    tileH(TILEH),
    GameObject(game, name)
{
    LoadMapXml(fileName + ".tmx");
    //PhysWorld* phys = new PhysWorld();
    CollisionsInMap = new PhysWorld();
    for (auto iter : mLayers) {
        iter->LayerTex = PreLayerTexBlit(mGame->GetRenderer(),iter);
    }
    if (!LoadCollision(fileName)) {
        SDL_Log("Collision init error.");
    }
}

GameFrame::MapObject::~MapObject()
{
}

void GameFrame::MapObject::update()
{
}

void GameFrame::MapObject::Draw(SDL_Renderer* renderer)
{
    for (auto iter : mLayers) {
        DrawLayer(renderer, iter);
    }
    for (auto iter : mObjectsInMap) {
        iter->Draw(renderer);
    }
}

void GameFrame::MapObject::DrawLayer(SDL_Renderer* renderer, Layer* layer)
{
    auto temp = GetGame()->GetCamera()->GetImageRect();
    SDL_Rect is = { 0,0,SCREEN_W, SCREEN_H };
    SDL_RenderCopy(renderer, layer->LayerTex, &temp, &is);
}

void GameFrame::MapObject::AddMapObject(GameObject* gameobject)
{
    mObjectsInMap.emplace_back(gameobject);
}

void GameFrame::MapObject::RemoveMapObject(GameObject* gameobject)
{
    auto iter = std::find(mObjectsInMap.begin(), mObjectsInMap.end(), gameobject);
    if (iter != mObjectsInMap.end()) {
        std::iter_swap(iter, mObjectsInMap.end() - 1);
        mObjectsInMap.pop_back();
    }
}

void GameFrame::MapObject::LoadMapXml(const std::string& filepath)
{
    //读取tmx格式地图文件
    TiXmlDocument doc(filepath.c_str());
    if (!doc.LoadFile()) {
        printf("Could not load test file %s. Error='%s'. Exiting.\n", filepath, doc.ErrorDesc());
        exit(1);
    }

    TiXmlElement* root = doc.RootElement();
    if (!root) {
        exit(1);
    }

    //处理地图属性
    auto name = root->Attribute("name");
    if (name) {
        MapName = name;
    }
    auto TLayer_width = root->Attribute("width");
    if (TLayer_width) {
        MapTileW = atoi(TLayer_width);
    }
    auto Tlayer_height = root->Attribute("height");
    if (Tlayer_height) {
        MapTileH = atoi(Tlayer_height);
    }

    int tmpTW = 16, tmpTH = 16;

    auto tw = root->Attribute("tilewidth");
    if (tw) {
        tmpTW = atoi(tw);
    }

    auto hw = root->Attribute("tileheight");
    if (hw) {
        tmpTH = atoi(hw);
    }

    //处理下一节点标签tileset
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
        L->layerTileW = tmpTW;
        L->layerTileH = tmpTH;
        L->LayerName = attr->Attribute("name");
        L->mesh_LayerWidth = atoi(attr->Attribute("width"));
        L->mesh_LayerHeight = atoi(attr->Attribute("height"));
        L->pixel_layerWidth = L->mesh_LayerWidth * L->layerTileW;
        L->pixel_layerHeight = L->mesh_LayerHeight * L->layerTileH;
        L->zlibcode = layer->FirstChild()->ToElement()->GetText();
        L->UpdateOrder = layercount;
        size_t output_length = 0;
        MapW = L->mesh_LayerWidth * tileW;
        MapH = L->mesh_LayerHeight * tileH;
        UncompressTile_By_Py(L);
        mLayers.emplace_back(L);
        layer = layer->NextSibling();//获取到下一个兄弟节点
    }
}

void GameFrame::MapObject::UncompressTile_By_Py(Layer* layer)
{
    const char* zlibcode = layer->zlibcode;
    PyObject* pZlibCode = PyUnicode_DecodeUTF8(zlibcode, strlen(zlibcode), NULL);
    PyObject*  pModule = PyImport_ImportModule("uncompress");
    if (pModule != NULL) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "UncompressFc");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* pArgs = PyTuple_Pack(3,pZlibCode, PyLong_FromLong(layer->mesh_LayerWidth), PyLong_FromLong(layer->mesh_LayerHeight));
            PyObject* pReturn = PyEval_CallObject(pFunc, pArgs);
            if (pReturn != NULL) {
                //将元组所有的参数一个个转换成int并存起来
                for (int i = 0; i < layer->mesh_LayerHeight * layer->mesh_LayerWidth; i++) {
                    PyObject* b = PyTuple_GetItem(pReturn, i);
                    int c;
                    PyArg_Parse(b, "i", &c);
                    layer->Lcode.emplace_back(c - 1);
                }
            }
            Py_DECREF(pFunc);
            Py_DECREF(pArgs);
            Py_DECREF(pReturn);
        }
    }
    Py_DECREF(pModule);
    Py_DECREF(pZlibCode);
}


int GameFrame::MapObject::LoadCollision(const std::string& path) {
    std::ifstream jsonFile(path+".json");
    if (!jsonFile.is_open()) {
        SDL_Log("Load json error.");;
        return 0;
    }

    // 读取JSON数据
    json jsonData;
    jsonFile >> jsonData;

    // 关闭文件
    jsonFile.close();

    // 遍历数组中的每组数据
    for (const auto& data : jsonData) {
        if (data.is_object()) {
            // 从每组数据中提取 x、y、w、h
            int x = data["x"];
            int y = data["y"];
            int w = data["w"];
            int h = data["h"];
            mGame->GetPhysSpace()->AddRigid();

        }
    }
    return 1;
}

SDL_Texture* GameFrame::Layer::PreLayerTexBlit(SDL_Renderer* renderer)
{
    SDL_Surface* SrcSurf = IMG_Load("sprite/tilesheet_0.png");
    SDL_Texture* SrcTex = SDL_CreateTextureFromSurface(renderer, SrcSurf);
    //创建透明表面，表面大小是地图实际尺寸而非图层原尺寸
    SDL_Surface* TargetSurf = SDL_CreateRGBSurfaceWithFormat(0, MapW, MapH, 32, SDL_PIXELFORMAT_RGBA32);
    /*int textureW = layer->pixel_layerWidth;
    int textureH = layer->pixel_layerHeight;*/
    int it = 0;
    SDL_Rect imageRect{ 0, 0, layer->layerTileW, layer->layerTileH };
    SDL_Rect dstRect{ 0, 0, TILEW, TILEH };
    for (auto iter : layer->Lcode) {
        if (iter == -1) {
            it++;
            continue;//-1意味着该处没有像素
        }

        //获得图片id，转换为贴图获取坐标
        Vector2 idvec = layer->TileIdParser(iter, SrcTex);
        imageRect.x = idvec.x * layer->layerTileW;
        imageRect.y = idvec.y * layer->layerTileH;

        //将格子id转换为绘制目标坐标
        Vector2 itvec = layer->MapIdParser(it);
        dstRect.x = itvec.x * TILEW;
        dstRect.y = itvec.y * TILEH;

        //生成合并纹理
        if (SDL_BlitScaled(SrcSurf, &imageRect, TargetSurf, &dstRect)!= 0) {
            SDL_Log("generate surface error.");
        }
        it++;
    };
    SDL_Texture* DecTex = SDL_CreateTextureFromSurface(renderer, TargetSurf);
    SDL_FreeSurface(SrcSurf);
    SDL_FreeSurface(TargetSurf);
    layer->LayerTex = DecTex;
    return DecTex;
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

GameFrame::Layer::Layer():
    LayerTex(nullptr)
{
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
    vec.x = it % mesh_LayerWidth;
    vec.y = it / mesh_LayerWidth;
    return vec;
}

