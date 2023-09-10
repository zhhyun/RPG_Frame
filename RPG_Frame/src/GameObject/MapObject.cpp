#include	"MapObject.h"
#include	"Game.h"
#include    <Python.h>
#include    <stdlib.h>
#include    <algorithm>
#include    "Math2.h"
//#include    <lua.hpp>

//sence��ʼ���Ĺ���Ӧ��ֻ������ȡ�ļ����ݲ����档û��ҪԤ������������Ҫʹ��ʱ����������Ҳ����
GameFrame::Sence::Sence(MapObject* map, const std::string& fileName) :
    tileW(TILEW),
    tileH(TILEH),
    SenceName(fileName),
    mSence(map)
{
    LoadSenceXml("MAP/" + fileName + ".tmx");
    mSence->AddSence(this);
}

GameFrame::Sence::~Sence()
{
    for (auto layer : mLayers) {
        delete layer;
    }
}

void GameFrame::Sence::update()
{
    CheckinRegion(mSence->GetGame()->GetPlayer());
}

void GameFrame::Sence::Draw(SDL_Renderer* renderer)
{
    DrawLayer(renderer, layerTex[0]);
    DrawAnimTile(renderer);
    if (GetStandTileFromObejctLayer(Player->GetComponent<CollisionComponent>()->GetCollisionPosA())) {
        Player->Draw(renderer);
        DrawLayer(renderer, layerTex[1]);
    }
    else {
        DrawLayer(renderer, layerTex[1]);
        Player->Draw(renderer);
    }
}

void GameFrame::Sence::DrawLayer(SDL_Renderer* renderer, SDL_Texture* layerTex)
{
    auto temp = mSence->GetGame()->GetCamera()->GetImageRect();

    SDL_Rect RectArea = { 0,0,SCREEN_W, SCREEN_H };
    //��������Ŀ�����꣬ȷ�����ڳߴ�С����Ļ�ĳ������ж���
    if (temp.w < RectArea.w){
        RectArea.w = temp.w;
        RectArea.x += 0.5 * (SCREEN_W - temp.w);
    }
    if (temp.h < RectArea.h) {
        RectArea.h = temp.h;
        RectArea.y += 0.5 * (SCREEN_H - temp.h);
    }
    if (SDL_RenderCopy(renderer, layerTex, &temp, &RectArea)) {
        const char* log = SDL_GetError();
        SDL_Log("layer render failed");
    }
}

void GameFrame::Sence::DrawAnimTile(SDL_Renderer* renderer)
{   
    for (auto layer : mLayers) {
        if (!layer->AnimaTiles.empty()) {
            for (auto& anima : layer->AnimaTiles) {
                Uint32 deltaTime = SDL_GetTicks() - anima.AnimTicks;
                float fm = (1 / anima.fps) * 1000.0f;
                if (deltaTime >= fm) {                   
                    anima.currFrame++;
                    anima.currFrame = anima.currFrame % anima.length;
                    anima.AnimTicks = SDL_GetTicks();
                } 

                SDL_Rect tilesrc = anima.tileSrc;
                tilesrc.x += (anima.currFrame * anima.tileSrc.w);
                Vector2 mappos = { anima.tileRect.x, anima.tileRect.y };
                Vector2 winpos = MapVecTransToWinVec(mappos);
                SDL_Rect tilerect = { winpos.x,winpos.y,anima.tileRect.w,anima.tileRect.h };
                SDL_RenderCopy(renderer, anima.tex, &tilesrc, &tilerect);

            }
            
        }
    }
}

void GameFrame::Sence::LoadSenceXml(const std::string& filepath)
{
    //��ȡtmx��ʽ��ͼ�ļ�
    TiXmlDocument doc;
    if (!doc.LoadFile(filepath.c_str())) {
        //log error;
        exit(1);
    }
    TiXmlElement* mapElement = doc.FirstChildElement("map");
  
    //�����ͼ����
    if (mapElement) {
        mapElement->QueryIntAttribute("width", &SenceTileW);
        mapElement->QueryIntAttribute("height", &SenceTileH);

        //����tileset
        TiXmlElement* tilesetElement = mapElement->FirstChildElement("tileset");
        if (tilesetElement) {
            //����һ��layerֻ��һ��tileset�������ļǵ��޸�Layer��tileset����
            //const char* tilesetName = tilesetElement->Attribute("name");
            /*int firstGid = 0;
            tilesetElement->QueryIntAttribute("firstgid", &firstGid);*/

            //����tile,һ�ִ���һ��tile
            TiXmlElement* TileElemet = tilesetElement->FirstChildElement("tile");
            int id=0;
            while (TileElemet) {
                Tile tile;
                tile.Tile_id = id;
                int idInload;//�ݴ��ȡ������id����
                //����tile_id
                TileElemet->QueryIntAttribute("id", &idInload);
                if (tile.Tile_id != idInload) {
                    Tileset.emplace_back(tile);
                    //TileElemet = TileElemet->NextSiblingElement("tile");
                    id++;
                    continue;
                }
                
                //�����ڵ���������ȡ�������û����������һ��tile�ڵ�
                TiXmlElement* PropertiesElemet = TileElemet->FirstChildElement("properties");
                if (PropertiesElemet) {
                    TiXmlElement* property = PropertiesElemet->FirstChildElement("property");
                    while (property) {
                        Property proty;
                        proty.Name.assign(property->Attribute("name"));
                        property->QueryIntAttribute("value", &proty.Value);
                        //����õ�������ӵ�tile��
                        tile.mProperties.emplace_back(proty);
                        property = property->NextSiblingElement("property");
                    }
                   // ���Դ������
                }
                else {
                    //��ӡ��Ϣ
                    SDL_Log("wanning:property load failed!");
                    //break;
                    //exit(1);
                }  
                Tileset.emplace_back(tile);
                TileElemet = TileElemet->NextSiblingElement("tile");
                id++;
            }
            //Tile������ͽ���
        }
        else {
            exit(1);
        }

        //����layer
        TiXmlElement* layerElement = mapElement->FirstChildElement("layer"); int layercount = 0;
        while (layerElement) {
            //·��Ӧ�ô��ļ���Ϣ���ȡ��������Դ���Ϊ�˷���ֱ�Ӹ���·��������Ӧ����
            //һ��ѭ������һ��ͼ��
            Layer* layer = new Layer(TIELPATH,this);
            if (layerElement->Attribute("visible")) {
                int t;
                layerElement->QueryIntAttribute("visible", &t);
                if (t == 0) {
                    layer->visible = true;
                }

            }

           // layer->zlibcode = layerElement->FirstChildElement("data")->GetText();
            layer->LayerName.assign(layerElement->Attribute("name"));
            mapElement->QueryIntAttribute("tilewidth", &layer->layerTileW);
            mapElement->QueryIntAttribute("tileheight", &layer->layerTileH);
            layerElement->QueryIntAttribute("width", &layer->mesh_LayerWidth);
            layerElement->QueryIntAttribute("height", &layer->mesh_LayerHeight);
            layer->pixel_layerWidth = layer->mesh_LayerWidth * layer->layerTileW;
            layer->pixel_layerHeight = layer->mesh_LayerHeight * layer->layerTileH;
            layer->UpdateOrder = layercount;

            TiXmlElement* PropertiesElemet = layerElement->FirstChildElement("properties");
            if (PropertiesElemet) {
                TiXmlElement* prop = PropertiesElemet->FirstChildElement("property");
                if (prop) {
                   layer->property.assign(prop->Attribute("name"));
                }
            }
             MapW = tileW * SenceTileW;
             MapH = tileH * SenceTileH;
             UncompressTile_By_Py(layer, layerElement->FirstChildElement("data")->GetText());
             mLayers.emplace_back(layer);
             layerElement = layerElement->NextSiblingElement("layer");
             layercount++;
        }

         //����object
         TiXmlElement* ObjectElement = mapElement->FirstChildElement("objectgroup");
         while (ObjectElement) {
                ObjectGroup Og;
                Og.name.assign(ObjectElement->Attribute("name"));
                if (ObjectElement->Attribute("visible")) {
                    int t;
                    ObjectElement->QueryIntAttribute("visible", &t);
                    if (t == 1) {
                        Og.visible = false;
                    }
                    else if (t == 0) {
                        Og.visible = true;
                    }
                }
                
                TiXmlElement* object = ObjectElement->FirstChildElement("object");
                while (object) {
                    Object obj;
                    object->QueryIntAttribute("x", &obj.x);
                    object->QueryIntAttribute("y", &obj.y);
                    object->QueryIntAttribute("width", &obj.width);
                    object->QueryIntAttribute("height", &obj.height);

                    TiXmlElement* PropertiesElemet = object->FirstChildElement("properties");
                    if (PropertiesElemet) {
                        TiXmlElement* property = PropertiesElemet->FirstChildElement("property");
                        while (property) {
                            Property proty;
                            proty.Name = property->Attribute("name");
                            property->QueryIntAttribute("value", &proty.Value);
                            //����õ�������ӵ�obj��
                            obj.mProperties.emplace_back(proty);
                            property = property->NextSiblingElement("property");
                        }
                    }
                    Og.mObjects.emplace_back(obj);
                    object = object->NextSiblingElement("object");
                }
                mObejctGroups.emplace_back(Og);
                ObjectElement = ObjectElement->NextSiblingElement("objectgroup");
         }
    }
    else
        exit(1);
}

GameFrame::Tile GameFrame::Sence::GetStandTileFromLayer(Vector2 standpos)
{
    //������ת��Ϊ���ӱ�ţ��鿴�������������һ��tile������������ȡ�� 
    standpos.x = std::floor(standpos.x / tileW);
    standpos.y = std::floor(standpos.y / tileH);
    int code = standpos.x  + standpos.y * SenceTileW;
    //code�Ǹ��Ӻ�,���Ӻ����0��ʼ����Ӧ����Ԫ���±�

    auto target_id = -10;
    if (code > Lcode.size()) {
        SDL_Log("code analyse error");
    }
    else {
        target_id = Lcode[code];
    }

    if (target_id == -1) {
        //SDL_Log("tile is transparent");
        Tile tilewithnull;
        tilewithnull.Tile_id = -1;
        return tilewithnull;
    }

    Tile* foundTile = nullptr;
    for (auto& tile : Tileset) {
        if (tile.Tile_id == target_id) {
            foundTile = &tile;
            break;
        }
    }

    if (foundTile != nullptr) {
        return *foundTile;
    }
    else {
        SDL_Log("no tile were found! ");
        Tile tilewithnull;
        tilewithnull.Tile_id = -2;
        return tilewithnull;
    }

}

bool GameFrame::Sence::GetStandTileFromObejctLayer(Vector2 standpos)
{
    //������ת��Ϊ���ӱ�ţ��鿴�������������һ��tile������������ȡ�� 
    standpos.x = std::floor(standpos.x / tileW);
    standpos.y = std::floor(standpos.y / tileH);
    int code = standpos.x + standpos.y * SenceTileW;
    //code�Ǹ��Ӻ�,���Ӻ����0��ʼ����Ӧ����Ԫ���±�
    int target_id;
    if (code > OLcode.size()) {
        SDL_Log("code analyse error");
    }
    else {
        target_id = OLcode[code];

        if (target_id == -1) {
            //SDL_Log("tile is transparent");
            Tile tilewithnull;
            tilewithnull.Tile_id = -1;
            return false;
        }
        else {
            for (auto& tile : Tileset) {
                if (tile.Tile_id == target_id) {
                    for (auto& prop : tile.mProperties) {
                        if (prop.Name == "v") {
                            return true;
                        }           
                    }
                     
                }
            }
            return false;
        }
    }
}

GameFrame::Object* GameFrame::Sence::GetStandTileFromObject(Vector2 standpos)
{
    for (auto& iter : mObejctGroups) {
        if (iter.name == "doors") {
            for (auto& region : iter.mObjects) {
                if (standpos.x/2 >= region.x &&
                    standpos.x/2 <= (region.x + region.width) &&
                    standpos.y/2 >= region.y &&
                    standpos.y/2 <= (region.y + region.height)) {
                    return &region;
                }
            }     
        }  
    }
    return nullptr;
}

GameFrame::Vector2 GameFrame::Sence::MapVecTransToWinVec(Vector2 mapPos)
{
    Vector2 tansVec;

    auto camera = Player->GetGame()->GetCamera();

    if (MapW < SCREEN_W) {
        SDL_Rect RectArea = { 0,0,SCREEN_W, SCREEN_H };
        //��������Ŀ�����꣬ȷ�����ڳߴ�С����Ļ�ĳ������ж���
        if (camera->GetImageRect().w < RectArea.w) {
            RectArea.w = camera->GetImageRect().w;
            //RectArea.x��С��ͼ�ڴ����еĺ�����
            RectArea.x += 0.5 * (SCREEN_W - camera->GetImageRect().w);
        }

        tansVec.x = mapPos.x + RectArea.x;
    }
    else {
        tansVec.x = mapPos.x - camera->GetImageRect().x;
    }


    if (MapH < SCREEN_H) {
        SDL_Rect RectArea = { 0,0,SCREEN_W, SCREEN_H };
        if (camera->GetImageRect().h < RectArea.h) {
            RectArea.h = camera->GetImageRect().h;
            RectArea.y += 0.5 * (SCREEN_H - camera->GetImageRect().h);
        }

        tansVec.y = mapPos.y + RectArea.y;
    }
    else {
        tansVec.y = mapPos.y - camera->GetImageRect().y;
    }
    return tansVec;
}

void GameFrame::Sence::CheckinRegion(GameObject* object)
{
    auto collComp = object->GetComponent<CollisionComponent>();
    if (collComp) {
        Object* obj = GetStandTileFromObject(collComp->GetAreaPos());
        bool IsFindTargetSence = false;
        Sence* sence = nullptr;
        int destid = -1;
        if (obj) {
            for (auto& propt : obj->mProperties) {
                if (propt.Name == "target_sence") {
                    IsFindTargetSence;
                    sence = mSence->GetSenceFromName(std::to_string(propt.Value));
                }
                if (propt.Name == "dst_id") {
                    destid = propt.Value;
                }
            }
            if (sence && destid != -1) {
                mSence->EnterSence(sence, destid);
            }
        }
    }
}

void GameFrame::Sence::Mergelayers_GeneraTex(SDL_Renderer* renderer)
{
    Layer* ground_layer = new Layer(*mLayers.front()); 
    ground_layer->LayerName = "CompeleteLayer";
    ground_layer->property = "GROUND_LAYER";
    ground_layer->visible = false;
    Layer* MaskBody_layer = new Layer(*mLayers.front());
    MaskBody_layer->LayerName = "CompeleteLayer";
    MaskBody_layer->property = "null";

    SDL_Surface* SrcSurf = IMG_Load(TIELPATH);
    SDL_Texture* SrcTex = SDL_CreateTextureFromSurface(renderer, SrcSurf);
    //����͸�����棬�����С�ǵ�ͼʵ�ʳߴ����ͼ��ԭ�ߴ�
    SDL_Surface* Ground_TargetSurf = SDL_CreateRGBSurfaceWithFormat(0, MapW, MapH, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_Surface* Mask_TargetSurf = SDL_CreateRGBSurfaceWithFormat(0, MapW, MapH, 32, SDL_PIXELFORMAT_RGBA32);

    for (auto iter : mLayers) {
        int it = 0;//it��Ŀ��λ�ñ�ţ�������
        if (iter->visible) {
            continue;
        }
        else {           
            for (auto code : iter->Lcode) {
                //code���زĴ���
                if (code == -1) {
                    //-1��ζ�Ÿô�û������
                }
                else {
                    ground_layer->Lcode[it] = code;
                    //���ͼƬid��ת��Ϊ��ͼ��ȡ����
                    Vector2 idvec = iter->TileIdParser(code, SrcTex);
                    SDL_Rect imageRect{
                        idvec.x * iter->layerTileW,
                        idvec.y * iter->layerTileH,
                        iter->layerTileW,
                        iter->layerTileH
                    };

                    //������idת��Ϊ����Ŀ������
                    Vector2 itvec = iter->MapIdParser(it);
                    SDL_Rect dstRect{
                        itvec.x * tileW,
                        itvec.y * tileH,
                        tileW,
                        tileH
                    };

                    //�����������ǲ��Ƕ����񣬲�������Ϣ
                    auto checktile = new Tile();
                    for (auto& tile : Tileset) {
                        if (tile.Tile_id == code) {
                            checktile = &tile;
                        }
                    }
                    
                    if (checktile) {
                        for (auto& prop : checktile->mProperties) {
                            if (prop.Name == "length") {
                                AnimaTile animTile;
                                animTile.length = prop.Value;
                                animTile.tileCode = code;
                                animTile.tileSrc = imageRect;
                                animTile.tileRect = dstRect;
                                animTile.tex = SrcTex;
                                iter->AnimaTiles.emplace_back(animTile);
                            }
                        }
                    }
                   

                    //���ɺϲ�����
                    if (iter->property == "GROUND_LAYER") {
                        if (SDL_UpperBlitScaled(SrcSurf, &imageRect, Ground_TargetSurf, &dstRect) != 0) {
                            SDL_Log("generate Ground_TargetSurf error.");
                        }
                    }
                    else {
                        MaskBody_layer->Lcode[it] = code;
                        if (SDL_UpperBlitScaled(SrcSurf, &imageRect, Mask_TargetSurf, &dstRect) != 0) {                            
                            SDL_Log("generate Mask_TargetSurf error.");
                        }
                    }
                }
                it++;
            };
           
        }
    }; 
    Lcode = ground_layer->Lcode; 
    OLcode = MaskBody_layer->Lcode;
    layerTex.emplace_back( SDL_CreateTextureFromSurface(renderer, Ground_TargetSurf) );
    layerTex.emplace_back( SDL_CreateTextureFromSurface(renderer, Mask_TargetSurf) );
    //SDL_DestroyTexture(SrcTex);
    SDL_FreeSurface(SrcSurf);
    SDL_FreeSurface(Ground_TargetSurf);
    SDL_FreeSurface(Mask_TargetSurf);
}

void GameFrame::Sence::UncompressTile_By_Py(Layer* layer,const char* zlibcode)
{
    PyObject* pZlibCode = PyUnicode_DecodeUTF8(zlibcode, strlen(zlibcode), NULL);
    PyObject*  pModule = PyImport_ImportModule("uncompress");
    if (pModule != NULL) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "UncompressFc");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* pArgs = PyTuple_Pack(3,pZlibCode, PyLong_FromLong(layer->mesh_LayerWidth), PyLong_FromLong(layer->mesh_LayerHeight));
            PyObject* pReturn = PyObject_Call(pFunc, pArgs, NULL);
            if (pReturn != NULL) {
                //��Ԫ�����еĲ���һ����ת����int��������
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

void GameFrame::Sence::ClearLayersTex()
{
    for (auto iter : layerTex) {
        SDL_DestroyTexture(iter);
        //delete iter;
    }
    layerTex.clear();
}

GameFrame::Layer::Layer(const std::string& FilePath, class Sence* sence):
    //LayerTex(nullptr),
    FilePath(FilePath),
    mSence(sence)
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

GameFrame::MapObject::MapObject(Game* game, const std::string& folderPath, const std::string& map_id):
    Map_id(map_id),
    GameObject(game, map_id, map_id)
{
    LoadSence(folderPath);
}

void GameFrame::MapObject::update()
{
    CurrSence->update();
}

void GameFrame::MapObject::Draw(SDL_Renderer* renderer)
{
    if (CurrSence) {
        CurrSence->Draw(renderer);
    }
}

GameFrame::Tile GameFrame::MapObject::GetStandTileFromLayer(Vector2 standpos)
{
    return CurrSence->GetStandTileFromLayer(standpos);
}

void GameFrame::MapObject::AddSence(Sence* sence)
{
    mSences.emplace_back(sence);
}

GameFrame::Sence* GameFrame::MapObject::GetSenceFromName(std::string senceName)
{
    for (auto sence : mSences) {
        if (sence->SenceName == senceName) {
            return sence;
        }
    }
    return nullptr;
}

void GameFrame::MapObject::LoadSence(const std::string& folderPath)
{ 
   Sence* main_sence = new Sence(this, "1000");
   Sence* cave2031 = new Sence(this, "2031");
   Sence* room2041 = new Sence(this, "2041");
   EnterSence(main_sence);
}

void GameFrame::MapObject::EnterSence(Sence* targetSence)
{ 
    //��ʼ��
    targetSence->Mergelayers_GeneraTex(mGame->GetRenderer());//��������
    if (CurrSence) {
        auto tmpPlayer = CurrSence->Player;
        tmpPlayer->ChangeMap(targetSence);
        LeaveCurrSence();
        targetSence->Player = tmpPlayer;
    }
    CurrSence = targetSence;  
}

void GameFrame::MapObject::EnterSence(Sence* targetSence, int destid)
{
    mGame->SetProcessEvent(false);
    //��ʼ��
    targetSence->Mergelayers_GeneraTex(mGame->GetRenderer());//��������
    
    if (CurrSence) {
        auto tmpPlayer = CurrSence->Player;
        tmpPlayer->ChangeMap(targetSence);
        Object* ReturnObj = new Object();
        Vector2 newPos;
        for (auto& iter : targetSence->mObejctGroups) {
            for (auto& obj : iter.mObjects) {
                for (auto& prop : obj.mProperties) {
                    if (prop.Name == "id") {
                        if (prop.Value == destid) {
                            *ReturnObj =  obj;
                            break;
                        }
                    }
                }
            }
        }

        if (ReturnObj) {
            for (auto& iter : ReturnObj->mProperties) {
                if (iter.Name == "x") {
                    newPos.x = iter.Value * targetSence->tileW;
                }
                if (iter.Name == "y") {
                    newPos.y = iter.Value * targetSence->tileH;
                }
            }
            tmpPlayer->SetPosition(newPos);
        }

        LeaveCurrSence();
        targetSence->Player = tmpPlayer;
    }
    CurrSence = targetSence;
    //���̸���
    mGame->GetCamera()->Update();

    mGame->SetProcessEvent(true);
}

void GameFrame::MapObject::LeaveCurrSence()
{
    //�ͷ�����
    CurrSence->ClearLayersTex();
    CurrSence->Player = nullptr;
}