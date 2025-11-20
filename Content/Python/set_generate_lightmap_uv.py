# python
import unreal

selected = unreal.EditorUtilityLibrary.get_selected_assets()
if not selected:
    unreal.log_warning("No assets selected.")
for asset in selected:
    if not isinstance(asset, unreal.StaticMesh):
        unreal.log_warning("{} is not a StaticMesh".format(asset.get_name()))
        continue

    print(unreal.EditorStaticMeshLibrary.set_generate_lightmap_uv(asset, True))
    asset.modify()
    unreal.EditorAssetLibrary.save_loaded_asset(asset)