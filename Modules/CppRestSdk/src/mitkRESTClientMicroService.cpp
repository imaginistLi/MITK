#include "mitkRESTClientMicroService.h"
#include "mitkRESTUtil.h"
#include <mitkCommon.h>

mitk::RESTClientMicroService::RESTClientMicroService() {}

mitk::RESTClientMicroService::~RESTClientMicroService() {}

pplx::task<web::json::value> mitk::RESTClientMicroService::Get(web::uri uri)
{
  MitkClient *client = new MitkClient(uri);

  MITK_INFO << "Calling GET with " << utility::conversions::to_utf8string(uri.path()) << " on client "
            << mitk::RESTUtil::convertToUtf8(uri.authority().to_string());

  MitkRequest getRequest(MitkRESTMethods::GET);
  // getRequest.set_request_uri(uri);

  return client->request(getRequest).then([=](MitkResponse response) {
    auto status = response.status_code();
    MITK_INFO << " status: " << status;

    if (status != web::http::status_codes::OK)
    {
      mitkThrow() << "response was not OK";
    }
    return response.extract_json().get();
  });
  // answer.wait();
  // return answer.get();
}

pplx::task<web::json::value> mitk::RESTClientMicroService::PUT(web::uri uri, web::json::value content)
{
  MitkClient *client = new MitkClient(uri);
  MITK_INFO << "Calling PUT with " << utility::conversions::to_utf8string(uri.path()) << " on client "
            << mitk::RESTUtil::convertToUtf8(uri.authority().to_string());

  MitkRequest putRequest(MitkRESTMethods::PUT);
  // putRequest.set_request_uri(uri);
  putRequest.set_body(content);

  return client->request(putRequest).then([=](MitkResponse response) {
    auto status = response.status_code();
    MITK_INFO << " status: " << status;

    if (status != web::http::status_codes::OK)
    {
      mitkThrow() << "response was not OK";
    }

    return response.extract_json().get();
  });
}

pplx::task<web::json::value> mitk::RESTClientMicroService::POST(web::uri uri, web::json::value content)
{
  MitkClient *client = new MitkClient(uri);
  MITK_INFO << "Calling POST with " << utility::conversions::to_utf8string(uri.path()) << " on client "
            << mitk::RESTUtil::convertToUtf8(uri.authority().to_string());

  MitkRequest postRequest(MitkRESTMethods::POST);
  if (content != NULL)
  {
    postRequest.set_body(content);
  }

  return client->request(postRequest).then([=](MitkResponse response) {
    try
    {
      auto status = response.status_code();
      MITK_INFO << " status: " << status;

      if (status != web::http::status_codes::Created)
      {
        mitkThrow() << "response was not OK";
      }

      return response.extract_json().get();
    }
    catch (...)
    {
      MITK_WARN << "Exception in Client Class";
    }
  });
}
