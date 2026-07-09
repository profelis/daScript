options gen2
options indenting = 4

require dastest/testing_boost public
require gltf/gltf_pbr_common
require math

def private near(t : T?; got, want, eps : float) {
    t |> success(abs(got - want) < eps, "expected {want}, got {got}")
}

def private near3(t : T?; got, want : float3; eps : float) {
    t |> success(length(got - want) < eps, "expected {want}, got {got}")
}

[test]
def test_skin_point(t : T?) {
    t |> run("identity palette returns the point") @(t : T?) {
        let m = identity4x4()
        let p = float4(1., 2., 3., 1.)
        t |> equal(gltf_skin_point(m, m, m, m, float4(0.25, 0.25, 0.25, 0.25), p), p)
    }
    t |> run("weights blend translated points") @(t : T?) {
        var ta = identity4x4()
        ta[3] = float4(2., 0., 0., 1.)
        var tb = identity4x4()
        tb[3] = float4(0., 4., 0., 1.)
        let p = float4(0., 0., 0., 1.)
        // 0.5/0.5 blend of the two translations = their average
        let blended = gltf_skin_point(ta, tb, identity4x4(), identity4x4(), float4(0.5, 0.5, 0., 0.), p)
        t |> equal(blended, float4(1., 2., 0., 1.))
    }
    t |> run("w=0 directions ignore translation") @(t : T?) {
        var ta = identity4x4()
        ta[3] = float4(5., 6., 7., 1.)
        let n = float4(0., 0., 1., 0.)
        t |> equal(gltf_skin_point(ta, ta, ta, ta, float4(1., 0., 0., 0.), n), n)
    }
}

[test]
def test_brdf_terms(t : T?) {
    let n = float3(0., 0., 1.)
    t |> run("fresnel at grazing/normal incidence") @(t : T?) {
        let f0 = float3(0.04, 0.04, 0.04)
        near3(t, gltf_fresnel_schlick(1.0, f0), f0, 1e-6)                     // head-on -> f0
        near3(t, gltf_fresnel_schlick(0.0, f0), float3(1., 1., 1.), 1e-6)     // grazing -> 1
    }
    t |> run("ggx distribution peaks at 1/pi for roughness 1") @(t : T?) {
        near(t, gltf_ggx_distribution(n, n, 1.0), 1.0 / 3.14159265, 1e-5)
    }
    t |> run("smith geometry is in (0, 1]") @(t : T?) {
        let v = normalize(float3(0.3, 0.2, 1.))
        let l = normalize(float3(-0.4, 0.1, 1.))
        let g = gltf_ggx_geometry_smith(n, v, l, 0.5)
        t |> success(g > 0.0 && g <= 1.0, "geometry term out of range")
    }
    t |> run("direct term is black when light is behind") @(t : T?) {
        let v = float3(0., 0., 1.)
        let l = float3(0., 0., -1.)   // below the surface -> ndotl = 0
        near3(t, gltf_pbr_direct(float3(1., 1., 1.), 0.0, 0.5, n, v, l, float3(3., 3., 3.)), float3(0., 0., 0.), 1e-6)
    }
}

[test]
def test_shading_helpers(t : T?) {
    t |> run("ambient occlusion strength blend") @(t : T?) {
        let albedo = float3(1., 1., 1.)
        let ambient = float3(0.2, 0.2, 0.2)
        near3(t, gltf_pbr_ambient(albedo, ambient, 1.0, 1.0), ambient, 1e-6)          // unoccluded
        near3(t, gltf_pbr_ambient(albedo, ambient, 0.0, 1.0), float3(0., 0., 0.), 1e-6) // fully occluded, full strength
        near3(t, gltf_pbr_ambient(albedo, ambient, 0.0, 0.0), ambient, 1e-6)          // strength 0 disables occlusion
    }
    t |> run("perturb_normal falls back without a tangent frame") @(t : T?) {
        let n = float3(0., 0., 1.)
        let bent = gltf_perturb_normal(n, float3(0., 0., 0.), 1.0, float3(1., 0., 0.), 1.0)
        t |> equal(bent, n)
    }
    t |> run("perturb_normal with a flat sample keeps the normal") @(t : T?) {
        let n = float3(0., 0., 1.)
        let tangent = float3(1., 0., 0.)
        near3(t, gltf_perturb_normal(n, tangent, 1.0, float3(0.5, 0.5, 1.0), 1.0), n, 1e-4)
    }
    t |> run("srgb encode endpoints") @(t : T?) {
        near3(t, gltf_srgb_encode(float3(0., 0., 0.)), float3(0., 0., 0.), 1e-6)
        near3(t, gltf_srgb_encode(float3(1., 1., 1.)), float3(1., 1., 1.), 1e-6)
    }
}
