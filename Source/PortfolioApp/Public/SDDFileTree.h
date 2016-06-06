// File Tree Viewer by Rama

#pragma once
#include "SCompoundWidget.h"
#include "STreeView.h"
#include "SlateHUD.h"
#include "SlateBasics.h"
//#include "STableRow.h"
//#include "STableViewBase.h"
//#include "WeakObjectPtrTemplates.h"
//
////DD File Tree Item
#include "DDFileTreeItem.h"

//~~~ Forward Declarations ~~~
//class UDDEdEngine;


typedef STreeView< FDDFileTreeItemPtr > SDDFileTreeView;

/**
* File Tree View
*/
class PORTFOLIOAPP_API SDDFileTree : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SDDFileTree)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class SlateHUD>, OwnerHUD)
		SLATE_END_ARGS()


		//~~~~~~~~
		//		DDEdEngine
		//~~~~~~~~
public:
	//owns this
//	TWeakObjectPtr<class UDDEdEngine> DDEdEngine;


	/** Refresh the Tree */
	//bool DoRefresh;


	//~~~
public:
	/** Widget constructor */
	void Construct(const FArguments& Args/*, TWeakObjectPtr<class UDDEdEngine> IN_DDEdEngine*/);

	/** Destructor */
	~SDDFileTree();

	/** @return Returns the currently selected category item */
	FDDFileTreeItemPtr GetSelectedDirectory() const;

	/** Selects the specified category */
	void SelectDirectory(const FDDFileTreeItemPtr& CategoryToSelect);

	/** @return Returns true if the specified item is currently expanded in the tree */
	bool IsItemExpanded(const FDDFileTreeItemPtr Item) const;

	UFUNCTION(BlueprintPure, Category = "VictoryBPLibrary|File IO")
		static bool PortFolio_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Diaporama")
		TArray<UTexture2D*> Images;


private:

	/** Called to generate a widget for the specified tree item */
	TSharedRef<ITableRow> DDFileTree_OnGenerateRow(FDDFileTreeItemPtr Item, const TSharedRef<STableViewBase>& OwnerTable);

	/** Given a tree item, fills an array of child items */
	void DDFileTree_OnGetChildren(FDDFileTreeItemPtr Item, TArray< FDDFileTreeItemPtr >& OutChildren);

	/** Called when the user clicks on an  item, or when selection changes by some other means */
	void DDFileTree_OnSelectionChanged(FDDFileTreeItemPtr Item, ESelectInfo::Type SelectInfo);

	/** Rebuilds the category tree from scratch */
	void RebuildFileTree();

	/** SWidget overrides */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:


	/** The tree view widget*/
	TSharedPtr< SDDFileTreeView > DDFileTreeView;

	/** The Core Data for the Tree Viewer! */
	TArray< FDDFileTreeItemPtr > Directories;
	TMap< FString, FDDFileTreeItemPtr > PathsToDirectories;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pointer to our parent HUD
	/////To make sure HUD's lifetime is controlled elsewhere, use "weak" ptr.
	/////HUD has "strong" pointer to Widget,
	/////circular ownership would prevent/break self-destruction of hud/widget (cause memory leak).
	TWeakObjectPtr<class SlateHUD> OwnerHUD;
};