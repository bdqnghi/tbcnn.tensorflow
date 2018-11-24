#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/StringProcessor/KnuthMorrisPratt.hpp"

namespace RadonFramework::Text::StringProcessors {

KnuthMorrisPratt::StorageType::StorageType()
:Position(0)
,Shift(0)
{
}

KnuthMorrisPratt::StorageType::~StorageType()
{
    delete[] Shift;
}

RF_Type::Bool KnuthMorrisPratt::Init(RF_Type::String& Text,
    const RF_Type::UInt32 Position,
    StorageType* Storage)
{
    Storage->Position = Position;
    // preprocessing
    RF_Type::Int32 i = 0, j = -1, m = Storage->Search.Length();
    if(Storage->Search.Length() > 0)
    {
        delete[] Storage->Shift;
        Storage->Shift = new RF_Type::Int32[m + 1];
        Storage->Shift[i] = j;
        while(i < m)
        {
            while(j >= 0 && Storage->Search[i] != Storage->Search[j])
                j = Storage->Shift[j];
            ++i;
            ++j;
            Storage->Shift[i] = j;
        }
    }
    return true;
}

void KnuthMorrisPratt::Reset(RF_Type::String& Text,
    const RF_Type::UInt32 Position,
    StorageType* Storage)
{
    Storage->Position = Position;
}

RF_Type::Int32 KnuthMorrisPratt::DoNext(RF_Type::String& Text,
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i = 0;
    while(Storage->Position < static_cast<RF_Type::Int32>(Text.Length()))
    {
        while(i > -1 && p2[i] != p1[Storage->Position])
            i = Storage->Shift[i];
        ++i;
        ++Storage->Position;
        if(i >= static_cast<RF_Type::Int32>(Storage->Search.Length()))
            return Storage->Position - i;
    }
    Storage->Position = -1;
    return Storage->Position;
}

RF_Type::Int32 KnuthMorrisPratt::DoAll(RF_Type::String& Text,
    StorageType* Storage)
{
    RF_Type::UInt8 const* p1 = (RF_Type::UInt8*)Text.c_str();
    RF_Type::UInt8 const* p2 = (RF_Type::UInt8*)Storage->Search.c_str();
    RF_Type::Int32 i = 0, hit = 0;
    while(Storage->Position < static_cast<RF_Type::Int32>(Text.Length()))
    {
        while(i > -1 && p2[i] != p1[Storage->Position])
            i = Storage->Shift[i];
        ++i;
        ++Storage->Position;
        if(i >= static_cast<RF_Type::Int32>(Storage->Search.Length()))
        {
            ++hit;
            i = Storage->Shift[i];
        }
    }
    return hit;
}

}