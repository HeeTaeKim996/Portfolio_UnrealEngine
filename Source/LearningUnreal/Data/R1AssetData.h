

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "R1AssetData.generated.h"




USTRUCT()
struct FAssetEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	FName AssetName;

	UPROPERTY(EditDefaultsOnly)
	FSoftObjectPath AssetPath;

	UPROPERTY(EditDefaultsOnly)
	TArray<FName> AssetLabels;
};

USTRUCT()
struct FAssetSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAssetEntry> AssetEntries;


};

/**
 *
 */
UCLASS()
class LEARNINGUNREAL_API UR1AssetData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// ※ 아래 세 함수는 코드 이해 안함. 한번 적고 다시 고칠일 없으니, 강의 코드 복붙
	virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;
	FSoftObjectPath GetAssetPathByName(const FName& AssetName);
	const FAssetSet& GetAssetSetByLabel(const FName& Label);

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAssetSet> AssetGroupNameToSet;

	UPROPERTY()
	TMap<FName, FSoftObjectPath> AssetNameToPath;

	UPROPERTY()
	TMap<FName, FAssetSet> AssetLabelToSet;
};
