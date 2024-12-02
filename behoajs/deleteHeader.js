/***********************************************
> deleteHeader by NguyenHoa
***********************************************/
const version = 'V1.0.2';

function setHeaderValue(headers, key, value) {
  const lowerCaseKey = key.toLowerCase();
  if (lowerCaseKey in headers) {
    headers[lowerCaseKey] = value;
  } else {
    headers[key] = value;
  }
}

const modifiedHeaders = $request.headers;
setHeaderValue(modifiedHeaders, "X-RevenueCat-ETag", "");
$done({ headers: modifiedHeaders });
