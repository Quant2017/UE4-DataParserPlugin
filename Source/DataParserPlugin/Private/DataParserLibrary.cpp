// Fill out your copyright notice in the Description page of Project Settings.

#include "DataParserLibrary.h"
#include <string>
//#if (WITH_LIBXL_BINDING == 1)
#include "libxl.h"
//#endif


DEFINE_LOG_CATEGORY(DataParserLibrary)



UDataParserLibrary::UDataParserLibrary(const FObjectInitializer & ObjectInitializer)
    : Super(ObjectInitializer)
{

}

bool UDataParserLibrary::ParseFile(FString FileName)
{
    UE_LOG(DataParserLibrary, Warning, TEXT("Parse file %s"), *FileName);

    auto ansiPath = StringCast<ANSICHAR>(*FileName);
    const char *path = ansiPath.Get();
    bool ok = false;

    m_matrix.Empty();

    //#if (WITH_LIBXL_BINDING == 1)
    libxl::Book *book = xlCreateXMLBook();
    if (book)
    {
        UE_LOG(DataParserLibrary, Warning, TEXT("Book created"));
        std::string spath(path);
        std::wstring wpath(spath.begin(), spath.end());

        if (book->load(wpath.c_str()))
        {
            libxl::Sheet *sheet = book->getSheet(0);
            if (sheet)
            {
                UE_LOG(DataParserLibrary, Warning, TEXT("XML Processing"));
                ok = true;

                for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
                {
                    TArray<float> arow;
                    for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
                    {
                        libxl::CellType cellType = sheet->cellType(row, col);
                        if (cellType == libxl::CELLTYPE_NUMBER)
                        {
                            float f = sheet->readNum(row, col);
                            UE_LOG(DataParserLibrary, Warning, TEXT("(%d, %d) = %f"), col, row, f);
                            arow.Add(f);
                        }
                        else
                        {
                            UE_LOG(DataParserLibrary, Warning, TEXT("(%d, %d) [%d]"), col, row, static_cast<int32>(cellType));
                        }
                    }
                    UE_LOG(DataParserLibrary, Warning, TEXT("Elements in row %d"), arow.Num());
                    m_matrix.Add(arow);
                }
                UE_LOG(DataParserLibrary, Warning, TEXT("Rows count %d"), m_matrix.Num());

                UE_LOG(DataParserLibrary, Warning, TEXT("XML Processing complete"));
            }
            else
            {
                FString errMsg = FString(ANSI_TO_TCHAR(book->errorMessage()));
                UE_LOG(DataParserLibrary, Error, TEXT("Error %s"), *errMsg);
            }
        }
        else
        {
            FString errMsg = FString(ANSI_TO_TCHAR(book->errorMessage()));
            UE_LOG(DataParserLibrary, Error, TEXT("Error %s"), *errMsg);
        }

        book->release();
    }
    else
    {
        UE_LOG(DataParserLibrary, Error, TEXT("Book load failed"));
    }
    //#endif

    return ok;
}

int32 UDataParserLibrary::GetArraysCount()
{
    return m_matrix.Num();
}

TArray<float>& UDataParserLibrary::GetArray(int32 Index)
{
    return m_matrix[Index];
}
