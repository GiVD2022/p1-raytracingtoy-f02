QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -O1 -Wno-expansion-to-defined -Wno-unused-parameter


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES = resources.qrc

SOURCES += \
    Controller.cpp \
    DataInOut/AttributeMapping.cpp \
    DataInOut/Output.cpp \
    DataInOut/VisualMapping.cpp \
    Main.cpp \
    Model/Builder.cpp \
    Model/Modelling/Animation.cpp \
    Model/Modelling/Lights/Light.cpp \
    Model/Modelling/Lights/LightFactory.cpp \
    Model/Modelling/Lights/PointLight.cpp \
    Model/Modelling/Materials/ColorMapStatic.cpp \
    Model/Modelling/Materials/Lambertian.cpp \
    Model/Modelling/Materials/Material.cpp \
    Model/Modelling/Materials/MaterialFactory.cpp \
    Model/Modelling/Materials/Texture.cpp \
    Model/Modelling/Objects/Box.cpp \
    Model/Modelling/Objects/Face.cpp \
    Model/Modelling/Objects/FittedPlane.cpp \
    Model/Modelling/Objects/Mesh.cpp \
    Model/Modelling/Objects/Object.cpp \
    Model/Modelling/Objects/ObjectFactory.cpp \
    Model/Modelling/Objects/Plane.cpp \
    Model/Modelling/Objects/Sphere.cpp \
    Model/Modelling/Scene.cpp \
    Model/Modelling/SceneFactory.cpp \
    Model/Modelling/SceneFactoryData.cpp \
    Model/Modelling/SceneFactoryVirtual.cpp \
    Model/Modelling/TG/TG.cpp \
    Model/Modelling/TG/TranslateTG.cpp \
    Model/Rendering/Camera.cpp \
    Model/Rendering/ColorShading.cpp \
    Model/Rendering/ColorShadow.cpp \
    Model/Rendering/DepthShading.cpp \
    Model/Rendering/NormalShading.cpp \
    Model/Rendering/RayTracer.cc \
    Model/Rendering/SetUp.cpp \
    Model/Rendering/ShadingFactory.cpp \
    View/CameraMenu.cpp \
    View/Label.cpp \
    View/MainWindow.cpp

HEADERS += \
    Controller.hh \
    DataInOut/AttributeMapping.hh \
    DataInOut/Output.hh \
    DataInOut/Serializable.hh \
    DataInOut/VisualMapping.hh \
    Model/Builder.hh \
    Model/Modelling/Animation.hh \
    Model/Modelling/Hitable.hh \
    Model/Modelling/Lights/Light.hh \
    Model/Modelling/Lights/LightFactory.hh \
    Model/Modelling/Lights/PointLight.hh \
    Model/Modelling/Materials/ColorMap.hh \
    Model/Modelling/Materials/ColorMapStatic.hh \
    Model/Modelling/Materials/Lambertian.hh \
    Model/Modelling/Materials/Material.hh \
    Model/Modelling/Materials/MaterialFactory.hh \
    Model/Modelling/Materials/Texture.hh \
    Model/Modelling/Objects/Box.hh \
    Model/Modelling/Objects/Face.hh \
    Model/Modelling/Objects/FittedPlane.hh \
    Model/Modelling/Objects/Mesh.hh \
    Model/Modelling/Objects/Object.hh \
    Model/Modelling/Objects/ObjectFactory.hh \
    Model/Modelling/Objects/Plane.hh \
    Model/Modelling/Objects/Sphere.hh \
    Model/Modelling/Ray.hh \
    Model/Modelling/Scene.hh \
    Model/Modelling/SceneFactory.hh \
    Model/Modelling/SceneFactoryData.hh \
    Model/Modelling/SceneFactoryVirtual.hh \
    Model/Modelling/TG/TG.hh \
    Model/Modelling/TG/TranslateTG.hh \
    Model/Rendering/Camera.hh \
    Model/Rendering/ColorShading.hh \
    Model/Rendering/ColorShadow.hh \
    Model/Rendering/DepthShading.h \
    Model/Rendering/NormalShading.h \
    Model/Rendering/RayTracer.hh \
    Model/Rendering/SetUp.hh \
    Model/Rendering/ShadingFactory.hh \
    Model/Rendering/ShadingStrategy.hh \
    View/CameraMenu.hh \
    View/Label.hh \
    View/MainWindow.hh \
    glm/core/_detail.hpp \
    glm/core/_detail.hpp \
    glm/core/_fixes.hpp \
    glm/core/_fixes.hpp \
    glm/core/_swizzle.hpp \
    glm/core/_swizzle.hpp \
    glm/core/_swizzle_func.hpp \
    glm/core/_swizzle_func.hpp \
    glm/core/_vectorize.hpp \
    glm/core/_vectorize.hpp \
    glm/core/func_common.hpp \
    glm/core/func_common.hpp \
    glm/core/func_common.inl \
    glm/core/func_common.inl \
    glm/core/func_exponential.hpp \
    glm/core/func_exponential.hpp \
    glm/core/func_exponential.inl \
    glm/core/func_exponential.inl \
    glm/core/func_geometric.hpp \
    glm/core/func_geometric.hpp \
    glm/core/func_geometric.inl \
    glm/core/func_geometric.inl \
    glm/core/func_integer.hpp \
    glm/core/func_integer.hpp \
    glm/core/func_integer.inl \
    glm/core/func_integer.inl \
    glm/core/func_matrix.hpp \
    glm/core/func_matrix.hpp \
    glm/core/func_matrix.inl \
    glm/core/func_matrix.inl \
    glm/core/func_noise.hpp \
    glm/core/func_noise.hpp \
    glm/core/func_noise.inl \
    glm/core/func_noise.inl \
    glm/core/func_packing.hpp \
    glm/core/func_packing.hpp \
    glm/core/func_packing.inl \
    glm/core/func_packing.inl \
    glm/core/func_trigonometric.hpp \
    glm/core/func_trigonometric.hpp \
    glm/core/func_trigonometric.inl \
    glm/core/func_trigonometric.inl \
    glm/core/func_vector_relational.hpp \
    glm/core/func_vector_relational.hpp \
    glm/core/func_vector_relational.inl \
    glm/core/func_vector_relational.inl \
    glm/core/hint.hpp \
    glm/core/hint.hpp \
    glm/core/intrinsic_common.hpp \
    glm/core/intrinsic_common.hpp \
    glm/core/intrinsic_common.inl \
    glm/core/intrinsic_common.inl \
    glm/core/intrinsic_exponential.hpp \
    glm/core/intrinsic_exponential.hpp \
    glm/core/intrinsic_exponential.inl \
    glm/core/intrinsic_exponential.inl \
    glm/core/intrinsic_geometric.hpp \
    glm/core/intrinsic_geometric.hpp \
    glm/core/intrinsic_geometric.inl \
    glm/core/intrinsic_geometric.inl \
    glm/core/intrinsic_matrix.hpp \
    glm/core/intrinsic_matrix.hpp \
    glm/core/intrinsic_matrix.inl \
    glm/core/intrinsic_matrix.inl \
    glm/core/intrinsic_trigonometric.hpp \
    glm/core/intrinsic_trigonometric.hpp \
    glm/core/intrinsic_trigonometric.inl \
    glm/core/intrinsic_trigonometric.inl \
    glm/core/intrinsic_vector_relational.hpp \
    glm/core/intrinsic_vector_relational.hpp \
    glm/core/intrinsic_vector_relational.inl \
    glm/core/intrinsic_vector_relational.inl \
    glm/core/setup.hpp \
    glm/core/setup.hpp \
    glm/core/type.hpp \
    glm/core/type.hpp \
    glm/core/type_float.hpp \
    glm/core/type_float.hpp \
    glm/core/type_gentype.hpp \
    glm/core/type_gentype.hpp \
    glm/core/type_gentype.inl \
    glm/core/type_gentype.inl \
    glm/core/type_half.hpp \
    glm/core/type_half.hpp \
    glm/core/type_half.inl \
    glm/core/type_half.inl \
    glm/core/type_int.hpp \
    glm/core/type_int.hpp \
    glm/core/type_mat.hpp \
    glm/core/type_mat.hpp \
    glm/core/type_mat.inl \
    glm/core/type_mat.inl \
    glm/core/type_mat2x2.hpp \
    glm/core/type_mat2x2.hpp \
    glm/core/type_mat2x2.inl \
    glm/core/type_mat2x2.inl \
    glm/core/type_mat2x3.hpp \
    glm/core/type_mat2x3.hpp \
    glm/core/type_mat2x3.inl \
    glm/core/type_mat2x3.inl \
    glm/core/type_mat2x4.hpp \
    glm/core/type_mat2x4.hpp \
    glm/core/type_mat2x4.inl \
    glm/core/type_mat2x4.inl \
    glm/core/type_mat3x2.hpp \
    glm/core/type_mat3x2.hpp \
    glm/core/type_mat3x2.inl \
    glm/core/type_mat3x2.inl \
    glm/core/type_mat3x3.hpp \
    glm/core/type_mat3x3.hpp \
    glm/core/type_mat3x3.inl \
    glm/core/type_mat3x3.inl \
    glm/core/type_mat3x4.hpp \
    glm/core/type_mat3x4.hpp \
    glm/core/type_mat3x4.inl \
    glm/core/type_mat3x4.inl \
    glm/core/type_mat4x2.hpp \
    glm/core/type_mat4x2.hpp \
    glm/core/type_mat4x2.inl \
    glm/core/type_mat4x2.inl \
    glm/core/type_mat4x3.hpp \
    glm/core/type_mat4x3.hpp \
    glm/core/type_mat4x3.inl \
    glm/core/type_mat4x3.inl \
    glm/core/type_mat4x4.hpp \
    glm/core/type_mat4x4.hpp \
    glm/core/type_mat4x4.inl \
    glm/core/type_mat4x4.inl \
    glm/core/type_size.hpp \
    glm/core/type_size.hpp \
    glm/core/type_vec.hpp \
    glm/core/type_vec.hpp \
    glm/core/type_vec.inl \
    glm/core/type_vec.inl \
    glm/core/type_vec1.hpp \
    glm/core/type_vec1.hpp \
    glm/core/type_vec1.inl \
    glm/core/type_vec1.inl \
    glm/core/type_vec2.hpp \
    glm/core/type_vec2.hpp \
    glm/core/type_vec2.inl \
    glm/core/type_vec2.inl \
    glm/core/type_vec3.hpp \
    glm/core/type_vec3.hpp \
    glm/core/type_vec3.inl \
    glm/core/type_vec3.inl \
    glm/core/type_vec4.hpp \
    glm/core/type_vec4.hpp \
    glm/core/type_vec4.inl \
    glm/core/type_vec4.inl \
    glm/ext.hpp \
    glm/ext.hpp \
    glm/glm.hpp \
    glm/glm.hpp \
    glm/gtc/constants.hpp \
    glm/gtc/constants.hpp \
    glm/gtc/constants.inl \
    glm/gtc/constants.inl \
    glm/gtc/epsilon.hpp \
    glm/gtc/epsilon.hpp \
    glm/gtc/epsilon.inl \
    glm/gtc/epsilon.inl \
    glm/gtc/half_float.hpp \
    glm/gtc/half_float.hpp \
    glm/gtc/half_float.inl \
    glm/gtc/half_float.inl \
    glm/gtc/matrix_access.hpp \
    glm/gtc/matrix_access.hpp \
    glm/gtc/matrix_access.inl \
    glm/gtc/matrix_access.inl \
    glm/gtc/matrix_integer.hpp \
    glm/gtc/matrix_integer.hpp \
    glm/gtc/matrix_inverse.hpp \
    glm/gtc/matrix_inverse.hpp \
    glm/gtc/matrix_inverse.inl \
    glm/gtc/matrix_inverse.inl \
    glm/gtc/matrix_transform.hpp \
    glm/gtc/matrix_transform.hpp \
    glm/gtc/matrix_transform.inl \
    glm/gtc/matrix_transform.inl \
    glm/gtc/noise.hpp \
    glm/gtc/noise.hpp \
    glm/gtc/noise.inl \
    glm/gtc/noise.inl \
    glm/gtc/quaternion.hpp \
    glm/gtc/quaternion.hpp \
    glm/gtc/quaternion.inl \
    glm/gtc/quaternion.inl \
    glm/gtc/random.hpp \
    glm/gtc/random.hpp \
    glm/gtc/random.inl \
    glm/gtc/random.inl \
    glm/gtc/reciprocal.inl \
    glm/gtc/reciprocal.inl \
    glm/gtc/swizzle.hpp \
    glm/gtc/swizzle.hpp \
    glm/gtc/swizzle.inl \
    glm/gtc/swizzle.inl \
    glm/gtc/type_precision.hpp \
    glm/gtc/type_precision.hpp \
    glm/gtc/type_precision.inl \
    glm/gtc/type_precision.inl \
    glm/gtc/type_ptr.hpp \
    glm/gtc/type_ptr.hpp \
    glm/gtc/ulp.hpp \
    glm/gtc/ulp.hpp \
    glm/gtc/ulp.inl \
    glm/gtc/ulp.inl \
    glm/gtx/associated_min_max.hpp \
    glm/gtx/associated_min_max.hpp \
    glm/gtx/associated_min_max.inl \
    glm/gtx/associated_min_max.inl \
    glm/gtx/bit.hpp \
    glm/gtx/bit.hpp \
    glm/gtx/bit.inl \
    glm/gtx/bit.inl \
    glm/gtx/closest_point.hpp \
    glm/gtx/closest_point.hpp \
    glm/gtx/closest_point.inl \
    glm/gtx/closest_point.inl \
    glm/gtx/color_cast.hpp \
    glm/gtx/color_cast.hpp \
    glm/gtx/color_cast.inl \
    glm/gtx/color_cast.inl \
    glm/gtx/color_space.hpp \
    glm/gtx/color_space.hpp \
    glm/gtx/color_space.inl \
    glm/gtx/color_space.inl \
    glm/gtx/color_space_YCoCg.hpp \
    glm/gtx/color_space_YCoCg.hpp \
    glm/gtx/color_space_YCoCg.inl \
    glm/gtx/color_space_YCoCg.inl \
    glm/gtx/compatibility.hpp \
    glm/gtx/compatibility.hpp \
    glm/gtx/compatibility.inl \
    glm/gtx/compatibility.inl \
    glm/gtx/component_wise.hpp \
    glm/gtx/component_wise.hpp \
    glm/gtx/component_wise.inl \
    glm/gtx/component_wise.inl \
    glm/gtx/constants.hpp \
    glm/gtx/constants.hpp \
    glm/gtx/epsilon.hpp \
    glm/gtx/epsilon.hpp \
    glm/gtx/euler_angles.hpp \
    glm/gtx/euler_angles.hpp \
    glm/gtx/euler_angles.inl \
    glm/gtx/euler_angles.inl \
    glm/gtx/extend.hpp \
    glm/gtx/extend.hpp \
    glm/gtx/extend.inl \
    glm/gtx/extend.inl \
    glm/gtx/extented_min_max.hpp \
    glm/gtx/extented_min_max.hpp \
    glm/gtx/extented_min_max.inl \
    glm/gtx/extented_min_max.inl \
    glm/gtx/fast_exponential.hpp \
    glm/gtx/fast_exponential.hpp \
    glm/gtx/fast_exponential.inl \
    glm/gtx/fast_exponential.inl \
    glm/gtx/fast_square_root.hpp \
    glm/gtx/fast_square_root.hpp \
    glm/gtx/fast_square_root.inl \
    glm/gtx/fast_square_root.inl \
    glm/gtx/fast_trigonometry.hpp \
    glm/gtx/fast_trigonometry.hpp \
    glm/gtx/fast_trigonometry.inl \
    glm/gtx/fast_trigonometry.inl \
    glm/gtx/gradient_paint.hpp \
    glm/gtx/gradient_paint.hpp \
    glm/gtx/gradient_paint.inl \
    glm/gtx/gradient_paint.inl \
    glm/gtx/handed_coordinate_space.hpp \
    glm/gtx/handed_coordinate_space.hpp \
    glm/gtx/handed_coordinate_space.inl \
    glm/gtx/handed_coordinate_space.inl \
    glm/gtx/inertia.hpp \
    glm/gtx/inertia.hpp \
    glm/gtx/inertia.inl \
    glm/gtx/inertia.inl \
    glm/gtx/int_10_10_10_2.hpp \
    glm/gtx/int_10_10_10_2.hpp \
    glm/gtx/int_10_10_10_2.inl \
    glm/gtx/int_10_10_10_2.inl \
    glm/gtx/integer.hpp \
    glm/gtx/integer.hpp \
    glm/gtx/integer.inl \
    glm/gtx/integer.inl \
    glm/gtx/intersect.hpp \
    glm/gtx/intersect.hpp \
    glm/gtx/intersect.inl \
    glm/gtx/intersect.inl \
    glm/gtx/log_base.hpp \
    glm/gtx/log_base.hpp \
    glm/gtx/log_base.inl \
    glm/gtx/log_base.inl \
    glm/gtx/matrix_cross_product.hpp \
    glm/gtx/matrix_cross_product.hpp \
    glm/gtx/matrix_cross_product.inl \
    glm/gtx/matrix_cross_product.inl \
    glm/gtx/matrix_interpolation.hpp \
    glm/gtx/matrix_interpolation.hpp \
    glm/gtx/matrix_interpolation.inl \
    glm/gtx/matrix_interpolation.inl \
    glm/gtx/matrix_major_storage.hpp \
    glm/gtx/matrix_major_storage.hpp \
    glm/gtx/matrix_major_storage.inl \
    glm/gtx/matrix_major_storage.inl \
    glm/gtx/matrix_operation.hpp \
    glm/gtx/matrix_operation.hpp \
    glm/gtx/matrix_operation.inl \
    glm/gtx/matrix_operation.inl \
    glm/gtx/matrix_query.hpp \
    glm/gtx/matrix_query.hpp \
    glm/gtx/matrix_query.inl \
    glm/gtx/matrix_query.inl \
    glm/gtx/mixed_product.hpp \
    glm/gtx/mixed_product.hpp \
    glm/gtx/mixed_product.inl \
    glm/gtx/mixed_product.inl \
    glm/gtx/multiple.hpp \
    glm/gtx/multiple.hpp \
    glm/gtx/multiple.inl \
    glm/gtx/multiple.inl \
    glm/gtx/noise.hpp \
    glm/gtx/noise.hpp \
    glm/gtx/norm.hpp \
    glm/gtx/norm.hpp \
    glm/gtx/norm.inl \
    glm/gtx/norm.inl \
    glm/gtx/normal.hpp \
    glm/gtx/normal.hpp \
    glm/gtx/normal.inl \
    glm/gtx/normal.inl \
    glm/gtx/normalize_dot.hpp \
    glm/gtx/normalize_dot.hpp \
    glm/gtx/normalize_dot.inl \
    glm/gtx/normalize_dot.inl \
    glm/gtx/number_precision.hpp \
    glm/gtx/number_precision.hpp \
    glm/gtx/number_precision.inl \
    glm/gtx/number_precision.inl \
    glm/gtx/ocl_type.hpp \
    glm/gtx/ocl_type.hpp \
    glm/gtx/ocl_type.inl \
    glm/gtx/ocl_type.inl \
    glm/gtx/optimum_pow.hpp \
    glm/gtx/optimum_pow.hpp \
    glm/gtx/optimum_pow.inl \
    glm/gtx/optimum_pow.inl \
    glm/gtx/orthonormalize.hpp \
    glm/gtx/orthonormalize.hpp \
    glm/gtx/orthonormalize.inl \
    glm/gtx/orthonormalize.inl \
    glm/gtx/perpendicular.hpp \
    glm/gtx/perpendicular.hpp \
    glm/gtx/perpendicular.inl \
    glm/gtx/perpendicular.inl \
    glm/gtx/polar_coordinates.hpp \
    glm/gtx/polar_coordinates.hpp \
    glm/gtx/polar_coordinates.inl \
    glm/gtx/polar_coordinates.inl \
    glm/gtx/projection.hpp \
    glm/gtx/projection.hpp \
    glm/gtx/projection.inl \
    glm/gtx/projection.inl \
    glm/gtx/quaternion.hpp \
    glm/gtx/quaternion.hpp \
    glm/gtx/quaternion.inl \
    glm/gtx/quaternion.inl \
    glm/gtx/random.hpp \
    glm/gtx/random.hpp \
    glm/gtx/raw_data.hpp \
    glm/gtx/raw_data.hpp \
    glm/gtx/raw_data.inl \
    glm/gtx/raw_data.inl \
    glm/gtx/reciprocal.hpp \
    glm/gtx/reciprocal.hpp \
    glm/gtx/rotate_vector.hpp \
    glm/gtx/rotate_vector.hpp \
    glm/gtx/rotate_vector.inl \
    glm/gtx/rotate_vector.inl \
    glm/gtx/simd_mat4.hpp \
    glm/gtx/simd_mat4.hpp \
    glm/gtx/simd_mat4.inl \
    glm/gtx/simd_mat4.inl \
    glm/gtx/simd_vec4.hpp \
    glm/gtx/simd_vec4.hpp \
    glm/gtx/simd_vec4.inl \
    glm/gtx/simd_vec4.inl \
    glm/gtx/spline.hpp \
    glm/gtx/spline.hpp \
    glm/gtx/spline.inl \
    glm/gtx/spline.inl \
    glm/gtx/std_based_type.hpp \
    glm/gtx/std_based_type.hpp \
    glm/gtx/std_based_type.inl \
    glm/gtx/std_based_type.inl \
    glm/gtx/string_cast.hpp \
    glm/gtx/string_cast.hpp \
    glm/gtx/string_cast.inl \
    glm/gtx/string_cast.inl \
    glm/gtx/transform.hpp \
    glm/gtx/transform.hpp \
    glm/gtx/transform.inl \
    glm/gtx/transform.inl \
    glm/gtx/transform2.hpp \
    glm/gtx/transform2.hpp \
    glm/gtx/transform2.inl \
    glm/gtx/transform2.inl \
    glm/gtx/ulp.hpp \
    glm/gtx/ulp.hpp \
    glm/gtx/unsigned_int.hpp \
    glm/gtx/unsigned_int.hpp \
    glm/gtx/unsigned_int.inl \
    glm/gtx/unsigned_int.inl \
    glm/gtx/vec1.hpp \
    glm/gtx/vec1.hpp \
    glm/gtx/vec1.inl \
    glm/gtx/vec1.inl \
    glm/gtx/vector_access.hpp \
    glm/gtx/vector_access.hpp \
    glm/gtx/vector_access.inl \
    glm/gtx/vector_access.inl \
    glm/gtx/vector_angle.hpp \
    glm/gtx/vector_angle.hpp \
    glm/gtx/vector_angle.inl \
    glm/gtx/vector_angle.inl \
    glm/gtx/vector_query.hpp \
    glm/gtx/vector_query.hpp \
    glm/gtx/vector_query.inl \
    glm/gtx/vector_query.inl \
    glm/gtx/verbose_operator.hpp \
    glm/gtx/verbose_operator.hpp \
    glm/gtx/verbose_operator.inl \
    glm/gtx/verbose_operator.inl \
    glm/gtx/wrap.hpp \
    glm/gtx/wrap.hpp \
    glm/gtx/wrap.inl \
    glm/gtx/wrap.inl \
    glm/virtrev/xstream.hpp \
    glm/virtrev/xstream.hpp


FORMS += \
    about.ui \
    camera.ui \
    main.ui

DISTFILES += \
    .gitignore \
    resources/box.json \
    resources/dadesBCN.json \
    resources/dadesBCNOneValue.json \
    resources/data0.json \
    resources/data10.json \
    resources/mapBCN.png \
    resources/mapZoom.png \
    resources/meshExample.json \
    resources/oneSphere.json \
    resources/setupDataBCN.json \
    resources/setupDataBCNOneValue.json \
    resources/setupRenderOneSphere.json \
    resources/setupRenderSpheres.json \
    resources/spheres.json \
    resources/twoSpheres.json


